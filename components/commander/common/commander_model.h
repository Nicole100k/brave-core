// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_MODEL_H_
#define BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_MODEL_H_

#include <string>
#include <vector>

#include "ui/gfx/range/range.h"

namespace commander {

struct CommandItemModel {
 public:
  CommandItemModel(const std::u16string& title,
                   const std::vector<gfx::Range>& matched_ranges,
                   const std::u16string& annotation);
  ~CommandItemModel();
  CommandItemModel(const CommandItemModel& other);

  std::u16string title;
  std::vector<gfx::Range> matched_ranges;
  std::u16string annotation;
};

// See chrome/browser/ui/commander/commander_view_model.h for details on these
// structs. They exist to get around some deps violations.
struct CommanderModel {
  enum Action { kDisplayResult, kClose, kPrompt };

 public:
  CommanderModel();
  ~CommanderModel();
  CommanderModel(const CommanderModel& other);

  int result_set_id;
  std::vector<CommandItemModel> items;
  std::u16string prompt_text;
  Action action;
};

}  // namespace commander

#endif  // BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_MODEL_H_
