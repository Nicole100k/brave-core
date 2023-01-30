// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/commander/command_centre.h"

#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/commander/commander_view_model.h"
#include "chrome/browser/ui/location_bar/location_bar.h"
#include "components/omnibox/browser/omnibox_view.h"

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
  LOG(ERROR) << "Toggle";
  backend_->Reset();

  auto* omnibox = browser->window()->GetLocationBar()->GetOmniboxView();
  omnibox->SetFocus(true);
  omnibox->SetUserText(u":> ");
  omnibox->SetCaretPos(3);
}

void CommandCentre::Show(Browser* browser) {
  LOG(ERROR) << "Show";
  auto* omnibox = browser->window()->GetLocationBar()->GetOmniboxView();
  omnibox->SetFocus(true);
  omnibox->SetUserText(u":> ");
  omnibox->SetCaretPos(3);
}

void CommandCentre::Hide() {
  backend_->Reset();
  // auto* omnibox = browser->window()->GetLocationBar()->GetOmniboxView();
  // omnibox->RevertAll();
  // omnibox->CloseOmniboxPopup();
  // no op
  LOG(ERROR) << "Should hide now!"
;}

void CommandCentre::OnViewModelUpdated(commander::CommanderViewModel model) {
  if (model.action == commander::CommanderViewModel::kPrompt) {
    Show(chrome::FindLastActive());
  }
  for (auto& observer : observers_) {
    observer.OnViewModelUpdated(model);
  }
}
