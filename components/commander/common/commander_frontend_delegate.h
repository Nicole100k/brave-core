// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_FRONTEND_DELEGATE_H_
#define BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_FRONTEND_DELEGATE_H_

#include <string>

#include "base/observer_list_types.h"
#include "brave/components/commander/common/commander_model.h"

namespace commander {
class CommanderFrontendDelegate {
 public:
  class Observer : public base::CheckedObserver {
   public:
    virtual void OnModelUpdated(const commander::CommanderModel& model) = 0;
  };

  static CommanderFrontendDelegate* Get();

  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;
  virtual void OnTextChanged(const std::u16string& text) = 0;

 protected:
  static void SetInstance(CommanderFrontendDelegate* instance);

 private:
  static CommanderFrontendDelegate* instance_;
};
}  // namespace commander

#endif  // BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_FRONTEND_DELEGATE_H_
