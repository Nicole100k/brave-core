// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_OMNIBOX_BROWSER_COMMANDER_PROVIDER_H_
#define BRAVE_COMPONENTS_OMNIBOX_BROWSER_COMMANDER_PROVIDER_H_

#include "chrome/browser/ui/commander/commander_frontend.h"
#include "chrome/browser/ui/webui/commander/commander_handler.h"
#include "components/omnibox/browser/autocomplete_input.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/autocomplete_provider.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_provider_listener.h"

class CommanderProvider : public CommanderHandler::Delegate,
                          public AutocompleteProvider {
 public:
  explicit CommanderProvider(AutocompleteProviderClient* client,
                             AutocompleteProviderListener* listener);
  ~CommanderProvider() override;
  CommanderProvider(const CommanderProvider&) = delete;
  CommanderProvider& operator=(const CommanderProvider&) = delete;

  void Start(const AutocompleteInput& input, bool minimal_changes) override;
  void DeleteMatch(const AutocompleteMatch& match) override;
};

#endif  // BRAVE_COMPONENTS_OMNIBOX_BROWSER_COMMANDER_PROVIDER_H_
