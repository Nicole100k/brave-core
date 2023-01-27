// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/omnibox/browser/commander_provider.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_provider_listener.h"

CommanderProvider::CommanderProvider(AutocompleteProviderClient* client,
                                     AutocompleteProviderListener* listener)
    // TODO: Might need to change this
    : AutocompleteProvider(AutocompleteProvider::TYPE_BUILTIN) {
  AddListener(listener);
}

CommanderProvider::~CommanderProvider() = default;

void CommanderProvider::Start(const AutocompleteInput &input, bool minimal_changes) {

}

void CommanderProvider::DeleteMatch(const AutocompleteMatch &match) {
  // Not implemented.
}
