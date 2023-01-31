// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BROWSER_UI_COMMANDER_COMMAND_CENTRE_H_
#define BRAVE_BROWSER_UI_COMMANDER_COMMAND_CENTRE_H_

#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/observer_list_types.h"
#include "chrome/browser/ui/commander/commander_backend.h"
#include "chrome/browser/ui/commander/commander_frontend.h"
#include "chrome/browser/ui/commander/commander_view_model.h"

class CommandCentre : public commander::CommanderFrontend {
 public:
  class Observer : public base::CheckedObserver {
   public:
    virtual void OnViewModelUpdated(
        const commander::CommanderViewModel& model) = 0;
  };

  explicit CommandCentre(commander::CommanderBackend* backend);
  CommandCentre(const CommandCentre&) = delete;
  CommandCentre& operator=(const CommandCentre&) = delete;
  ~CommandCentre() override;

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  // commander::CommanderFrontend:
  void ToggleForBrowser(Browser* browser) override;
  void Show(Browser* browser) override;
  void Hide() override;

 private:
  void OnViewModelUpdated(commander::CommanderViewModel model);

  raw_ptr<commander::CommanderBackend> backend_;
  base::ObserverList<Observer> observers_;
  base::WeakPtrFactory<CommandCentre> weak_ptr_factory_{this};
};

#endif  // BRAVE_BROWSER_UI_COMMANDER_COMMAND_CENTRE_H_
