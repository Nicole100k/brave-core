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
#include "brave/browser/ui/commander/command_centre.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/commander/commander.h"
#include "chrome/browser/ui/commander/commander_backend.h"
#include "chrome/browser/ui/commander/commander_view_model.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/autocomplete_match_type.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_provider_listener.h"

std::u16string CommanderProvider::last_text_ = u"";

CommanderProvider::CommanderProvider(AutocompleteProviderClient* client,
                                     AutocompleteProviderListener* listener)
    : AutocompleteProvider(AutocompleteProvider::TYPE_BRAVE_COMMANDER) {
  AddListener(listener);

  auto* frontend =
      static_cast<CommandCentre*>(commander::Commander::Get()->frontend());
  if (frontend) {
    frontend->AddObserver(this);
  }
}

CommanderProvider::~CommanderProvider() {
  auto* frontend =
      static_cast<CommandCentre*>(commander::Commander::Get()->frontend());
  if (frontend) {
    frontend->RemoveObserver(this);
  }
}

void CommanderProvider::Start(const AutocompleteInput& input,
                              bool minimal_changes) {
  last_input_ = input.text();
  Stop(true, false);
  if (base::StartsWith(input.text(), u":>")) {
    auto* backend = commander::Commander::Get()->backend();
    auto* browser = chrome::FindLastActive();
    if (!browser || !backend) {
      return;
    }

    std::u16string text(base::TrimWhitespace(
        input.text().substr(2), base::TrimPositions::TRIM_LEADING));
    if (text == last_text_) {
      return;
    }

    if (!IsInObserverList()) {
      static_cast<CommandCentre*>(commander::Commander::Get()->frontend())
          ->AddObserver(this);
    }
    last_text_ = text;
    backend->OnTextChanged(text, browser);
  }
}

void CommanderProvider::OnViewModelUpdated(
    const commander::CommanderViewModel& view_model) {
  if (view_model.action == commander::CommanderViewModel::kPrompt) {
    current_prompt_ = view_model.prompt_text;
  }

  matches_.clear();
  int rank = 10000;
  for (uint32_t i = 0; i < view_model.items.size(); ++i) {
    const auto& option = view_model.items[i];
    AutocompleteMatch match(this, rank--, false,
                            AutocompleteMatchType::BOOKMARK_TITLE);
    // This is neat but it would be nice if we could always show it instead of
    // only when we have a result selected.
    match.contents = option.annotation;
    match.additional_text = current_prompt_;
    if (!option.annotation.empty()) {
      match.contents_class = {
          ACMatchClassification(0, ACMatchClassification::DIM)};
    }
    match.keyword = u":> ";
    match.description = u":> " + option.title;
    match.allowed_to_be_default_match = true;
    match.scoring_signals.set_total_title_match_length(3);
    // We don't want to change the prompt at all while the user is going through
    // their options.
    match.fill_into_edit = last_input_;
    match.destination_url =
        GURL("brave-command://" + std::to_string(view_model.result_set_id) +
             "/" + std::to_string(i));
    match.description_class = {
        ACMatchClassification(0, ACMatchClassification::DIM),
        ACMatchClassification(2, ACMatchClassification::MATCH)};
    matches_.push_back(match);
  }

  NotifyListeners(true);
}
