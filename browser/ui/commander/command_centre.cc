// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/commander/command_centre.h"

#include <memory>

#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "brave/components/commander/common/commander_frontend_delegate.h"
#include "brave/components/commander/common/commander_model.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/commander/commander.h"
#include "chrome/browser/ui/commander/commander_view_model.h"
#include "chrome/browser/ui/location_bar/location_bar.h"
#include "components/omnibox/browser/omnibox_view.h"

namespace commander {
namespace {
CommandItemModel FromViewModel(const CommandItemViewModel& model) {
  return CommandItemModel(model.title, model.matched_ranges, model.annotation);
}
CommanderModel FromViewModel(const CommanderViewModel& model) {
  CommanderModel result;
  result.result_set_id = model.result_set_id;
  result.prompt_text = model.prompt_text;
  switch (model.action) {
    case CommanderViewModel::kDisplayResults:
      result.action = CommanderModel::kDisplayResult;
      break;
    case CommanderViewModel::kPrompt:
      result.action = CommanderModel::kPrompt;
      break;
    case CommanderViewModel::kClose:
      result.action = CommanderModel::kClose;
      break;
    default:
      NOTREACHED();
  }

  for (const auto& item : model.items) {
    result.items.push_back(FromViewModel(item));
  }
  return result;
}
}  // namespace
}  // namespace commander

CommandCentre::CommandCentre(commander::CommanderBackend* backend)
    : backend_(backend) {
  SetInstance(this);
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

void CommandCentre::OnTextChanged(const std::u16string& text) {
  backend_->OnTextChanged(text, chrome::FindLastActive());
}

void CommandCentre::ToggleForBrowser(Browser*) {
  backend_->Reset();

  auto* omnibox =
      chrome::FindLastActive()->window()->GetLocationBar()->GetOmniboxView();
  omnibox->SetFocus(true);
  omnibox->SetUserText(u":> ");
  omnibox->SetCaretPos(3);
}

void CommandCentre::Show(Browser*) {
  auto* omnibox =
      chrome::FindLastActive()->window()->GetLocationBar()->GetOmniboxView();
  omnibox->SetFocus(true);
  omnibox->SetUserText(u":> ");
  omnibox->SetCaretPos(3);
}

void CommandCentre::Hide() {
  backend_->Reset();
  auto* omnibox =
      chrome::FindLastActive()->window()->GetLocationBar()->GetOmniboxView();
  if (!omnibox->GetText().starts_with(u":>")) {
    return;
  }
  omnibox->RevertAll();
  omnibox->CloseOmniboxPopup();
}

void CommandCentre::OnViewModelUpdated(commander::CommanderViewModel vm) {
  auto model = commander::FromViewModel(vm);
  if (vm.action == commander::CommanderViewModel::kPrompt) {
    Show(chrome::FindLastActive());
  } else if (vm.action == commander::CommanderViewModel::kClose) {
    Hide();
  }
  for (auto& observer : observers_) {
    observer.OnModelUpdated(model);
  }
}

// static
std::unique_ptr<commander::CommanderFrontend>
commander::CommanderFrontend::Create(commander::CommanderBackend* backend) {
  return std::make_unique<CommandCentre>(backend);
}
