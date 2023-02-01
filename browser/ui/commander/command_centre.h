// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BROWSER_UI_COMMANDER_COMMAND_CENTRE_H_
#define BRAVE_BROWSER_UI_COMMANDER_COMMAND_CENTRE_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "brave/components/commander/common/commander_frontend_delegate.h"
#include "brave/components/commander/common/commander_model.h"
#include "chrome/browser/ui/commander/commander_frontend.h"
#include "chrome/browser/ui/commander/commander_view_model.h"

class OmniboxView;
class CommandCentre : public commander::CommanderFrontend,
                      public commander::CommanderFrontendDelegate {
 public:
  explicit CommandCentre(commander::CommanderBackend* backend);
  CommandCentre(const CommandCentre&) = delete;
  CommandCentre& operator=(const CommandCentre&) = delete;
  ~CommandCentre() override;

  // commander::CommanderFrontend:
  void ToggleForBrowser(Browser* browser) override;
  void Show(Browser* browser) override;
  void Hide() override;

  // commander::CommanderFrontendDelegate:
  void AddObserver(Observer* observer) override;
  void RemoveObserver(Observer* observer) override;
  void OnTextChanged(const std::u16string& text) override;

 private:
  OmniboxView* GetOmnibox();
  bool IsShowing();
  void OnViewModelUpdated(commander::CommanderViewModel model);

  std::u16string last_searched_;
  commander::CommanderModel last_model_;

  raw_ptr<commander::CommanderBackend> backend_;
  base::ObserverList<Observer> observers_;
  base::WeakPtrFactory<CommandCentre> weak_ptr_factory_{this};
};

#endif  // BRAVE_BROWSER_UI_COMMANDER_COMMAND_CENTRE_H_
