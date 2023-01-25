// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_SHORTCUTS_COMMON_MODIFIER_NAMES_H_
#define BRAVE_COMPONENTS_SHORTCUTS_COMMON_MODIFIER_NAMES_H_

#include <string>
#include <vector>

#include "ui/events/event_constants.h"
#include "ui/events/keycodes/keyboard_codes_posix.h"

namespace shortcuts {
std::string GetKeyName(ui::KeyboardCode code);
std::vector<std::string> GetModifierName(ui::KeyEventFlags flags);
}

#endif  // BRAVE_COMPONENTS_SHORTCUTS_COMMON_MODIFIER_NAMES_H_
