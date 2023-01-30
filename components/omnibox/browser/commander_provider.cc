// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/omnibox/browser/commander_provider.h"

#include <cmath>
#include <string>
#include <utility>

#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/commander/commander.h"
#include "chrome/browser/ui/commander/commander_backend.h"
#include "chrome/browser/ui/commander/commander_view_model.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/autocomplete_match_type.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_provider_listener.h"

CommanderProvider::CommanderProvider(AutocompleteProviderClient* client,
                                     AutocompleteProviderListener* listener)
    // TODO: Might need to change this
    : AutocompleteProvider(AutocompleteProvider::TYPE_BUILTIN) {
  AddListener(listener);
}

CommanderProvider::~CommanderProvider() {
  commander::Commander::Get()->backend()->SetUpdateCallback(base::DoNothing());
}

void CommanderProvider::Start(const AutocompleteInput& input,
                              bool minimal_changes) {
  matches_.clear();
  if (base::StartsWith(input.text(), u":>")) {
    auto* backend = commander::Commander::Get()->backend();
    auto* browser = chrome::FindLastActive();
    if (!browser || !backend) {
      return;
    }
    backend->SetUpdateCallback(
        base::BindRepeating(&CommanderProvider::OnCommandsReceived,
                            weak_ptr_factory_.GetWeakPtr()));

    std::u16string text(base::TrimWhitespace(
        input.text().substr(2), base::TrimPositions::TRIM_LEADING));
    backend->OnTextChanged(text, browser);
  }
}

void CommanderProvider::OnCommandsReceived(
    commander::CommanderViewModel view_model) {

  int rank = 100000000;
  for (uint32_t i = 0; i < view_model.items.size(); ++i) {
    const auto& option = view_model.items[i];
    AutocompleteMatch match(this, rank++, false,
                            AutocompleteMatchType::BOOKMARK_TITLE);
    // match.additional_text = option.annotation;
    // match.description = option.annotation;
    match.contents = option.annotation;
    if (!option.annotation.empty()) {
      match.contents_class = {
          ACMatchClassification(0, ACMatchClassification::DIM)};
    }
    match.keyword = u":> ";
    match.description = u":> " + option.title;
    match.allowed_to_be_default_match = true;
    match.scoring_signals.set_total_title_match_length(3);
    match.destination_url = GURL("brave-command://" + std::to_string(view_model.result_set_id) + "/" + std::to_string(i));
    match.description_class = {
        ACMatchClassification(0, ACMatchClassification::DIM),
        ACMatchClassification(2, ACMatchClassification::MATCH)};
    matches_.push_back(match);
  }

  NotifyListeners(true);
}
