// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/commander/command_centre.h"

#include <memory>
#include <string>

#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "brave/components/commander/common/commander_frontend_delegate.h"
#include "brave/components/commander/common/commander_model.h"
#include "brave/components/commander/common/constants.h"
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
  observer->OnModelUpdated(last_model_);
}

void CommandCentre::RemoveObserver(Observer* observer) {
  observers_.RemoveObserver(observer);
}

void CommandCentre::SetText(const std::u16string& text) {
  if (text == last_searched_ && last_model_.items.size() != 0) {
    return;
  }
  last_searched_ = text;
  backend_->OnTextChanged(text, chrome::FindLastActive());
}

void CommandCentre::SelectCommand(uint32_t command_index,
                                  uint32_t result_set_id) {
  backend_->OnCommandSelected(command_index, result_set_id);
}

void CommandCentre::ToggleForBrowser(Browser*) {
  if (IsShowing()) {
    Hide();
  } else {
    Show(chrome::FindLastActive());
  }
}

void CommandCentre::Show(Browser*) {
  auto* omnibox = GetOmnibox();
  omnibox->SetFocus(true);

  auto text = commander::kCommandPrefix + std::u16string(u" ");
  omnibox->SetUserText(text);
  omnibox->SetCaretPos(text.size());
}

void CommandCentre::Hide() {
  backend_->Reset();
  if (!IsShowing()) {
    return;
  }
  auto* omnibox = GetOmnibox();
  omnibox->RevertAll();
  omnibox->CloseOmniboxPopup();
}

OmniboxView* CommandCentre::GetOmnibox() {
  return chrome::FindLastActive()->window()->GetLocationBar()->GetOmniboxView();
}

bool CommandCentre::IsShowing() {
  return GetOmnibox()->GetText().starts_with(commander::kCommandPrefix);
}

void CommandCentre::OnViewModelUpdated(commander::CommanderViewModel vm) {
  last_model_ = commander::FromViewModel(vm);
  if (vm.action == commander::CommanderViewModel::kPrompt) {
    last_searched_ = u"";
    Show(chrome::FindLastActive());
  } else if (vm.action == commander::CommanderViewModel::kClose) {
    Hide();
    last_searched_ = u"";
  }

  for (auto& observer : observers_) {
    observer.OnModelUpdated(last_model_);
  }
}

// static
std::unique_ptr<commander::CommanderFrontend>
commander::CommanderFrontend::Create(commander::CommanderBackend* backend) {
  return std::make_unique<CommandCentre>(backend);
}
