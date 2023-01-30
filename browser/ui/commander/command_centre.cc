// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/commander/command_centre.h"

#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/commander/commander_view_model.h"

CommandCentre::CommandCentre(commander::CommanderBackend* backend)
    : backend_(backend) {
  backend_->SetUpdateCallback(base::BindRepeating(
      &CommandCentre::OnViewModelUpdated, weak_ptr_factory_.GetWeakPtr()));
}

CommandCentre::~CommandCentre() {
  backend_->SetUpdateCallback(base::DoNothing());
}

void CommandCentre::AddObserver(Observer* observer) {
  observers_.AddObserver(observer);
}

void CommandCentre::RemoveObserver(Observer* observer) {
  observers_.RemoveObserver(observer);
}

void CommandCentre::ToggleForBrowser(Browser* browser) {
  browser->SetFocusToLocationBar();
}

void CommandCentre::Show(Browser* browser) {
  browser->SetFocusToLocationBar();
}

void CommandCentre::Hide() {
  // no op
}

void CommandCentre::OnViewModelUpdated(commander::CommanderViewModel model) {
  for (auto& observer : observers_) {
    observer.OnViewModelUpdated(model);
  }
}
