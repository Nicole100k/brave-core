// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/omnibox/browser/commander_provider.h"
#include <string>
#include <utility>
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/strings/string_util.h"
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

  if (base::StartsWith(input.text(), u":> ")) {
    auto* backend = commander::Commander::Get()->backend();
    auto* browser = chrome::FindLastActive();
    if (!browser || !backend) {
      return;
    }
    backend->SetUpdateCallback(
        base::BindRepeating(&CommanderProvider::OnCommandsReceived,
                            weak_ptr_factory_.GetWeakPtr()));

    backend->OnTextChanged(input.text().substr(3), browser);
  }
}

void CommanderProvider::OnCommandsReceived(
    commander::CommanderViewModel view_model) {
  matches_.clear();

  for (const auto& option : view_model.items) {
    AutocompleteMatch match(this, 0, false,
                            AutocompleteMatchType::NAVSUGGEST_PERSONALIZED);
    match.contents = u":> " + option.title;
    match.contents_class = {
        ACMatchClassification(0, ACMatchClassification::DIM),
        ACMatchClassification(2, ACMatchClassification::MATCH)};
    matches_.push_back(match);
  }

  listeners_.front()->OnProviderUpdate(true, this);
}
