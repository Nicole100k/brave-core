// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_OMNIBOX_BROWSER_COMMANDER_PROVIDER_H_
#define BRAVE_COMPONENTS_OMNIBOX_BROWSER_COMMANDER_PROVIDER_H_

#include <string>
#include "base/memory/weak_ptr.h"
#include "brave/browser/ui/commander/command_centre.h"
#include "chrome/browser/ui/commander/commander_view_model.h"
#include "components/omnibox/browser/autocomplete_provider.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_provider_listener.h"
class CommanderProvider : public AutocompleteProvider, public CommandCentre::Observer {
 public:
  CommanderProvider(AutocompleteProviderClient* client,
                    AutocompleteProviderListener* listener);
  CommanderProvider(const CommanderProvider&) = delete;
  CommanderProvider& operator=(const CommanderProvider&) = delete;

  // AutocompleteProvider:
  void Start(const AutocompleteInput& input, bool minimal_changes) override;

 private:
  ~CommanderProvider() override;

  void OnViewModelUpdated(const commander::CommanderViewModel& view_model) override;

  std::u16string last_text_;
  base::WeakPtrFactory<CommanderProvider> weak_ptr_factory_{this};
};

#endif  // BRAVE_COMPONENTS_OMNIBOX_BROWSER_COMMANDER_PROVIDER_H_
