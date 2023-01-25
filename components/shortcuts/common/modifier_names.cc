// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/shortcuts/common/modifier_names.h"

namespace shortcuts {
std::vector<std::string> GetModifierName(ui::KeyEventFlags flags) {
  std::vector<std::string> result;

  if (flags & ui::EF_COMMAND_DOWN)
    result.push_back("Cmd");

  if (flags & ui::EF_CONTROL_DOWN)
    result.push_back("Ctrl");

  if (flags & ui::EF_ALT_DOWN)
    result.push_back("Alt");

  if (flags & ui::EF_SHIFT_DOWN)
    result.push_back("Shift");

  if (flags & ui::EF_FUNCTION_DOWN)
    result.push_back("Fn");

  return result;
}
}  // namespace shortcuts
