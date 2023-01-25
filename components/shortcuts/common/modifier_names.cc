// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/shortcuts/common/modifier_names.h"
#include "ui/events/keycodes/keyboard_codes_posix.h"
#include "ui/events/keycodes/keysym_to_unicode.h"

namespace shortcuts {
std::string GetKeyName(ui::KeyboardCode code) {
  switch (code) {
    case ui::VKEY_F1:
      return "F1";
    case ui::VKEY_F2:
      return "F2";
    case ui::VKEY_F3:
      return "F3";
    case ui::VKEY_F4:
      return "F4";
    case ui::VKEY_F5:
      return "F5";
    case ui::VKEY_F6:
      return "F6";
    case ui::VKEY_F7:
      return "F7";
    case ui::VKEY_F8:
      return "F8";
    case ui::VKEY_F9:
      return "F9";
    case ui::VKEY_F10:
      return "F10";
    case ui::VKEY_F11:
      return "F11";
    case ui::VKEY_F12:
      return "F12";
    case ui::VKEY_F13:
      return "F13";
    case ui::VKEY_F14:
      return "F14";
    case ui::VKEY_F15:
      return "F15";
    case ui::VKEY_F16:
      return "F16";
    case ui::VKEY_F17:
      return "F17";
    case ui::VKEY_F18:
      return "F18";
    case ui::VKEY_F19:
      return "F19";
    case ui::VKEY_F20:
      return "F20";
    case ui::VKEY_F21:
      return "F21";
    case ui::VKEY_F22:
      return "F22";
    case ui::VKEY_F23:
      return "F23";
    case ui::VKEY_F24:
      return "F24";
    case ui::VKEY_ESCAPE:
      return "Esc";
    case ui::VKEY_BROWSER_SEARCH:
      return "Search";
    case ui::VKEY_LMENU:
    case ui::VKEY_RMENU:
    case ui::VKEY_MENU:
      return "Menu";
    case ui::VKEY_BROWSER_FORWARD:
      return "Forward";
    case ui::VKEY_BROWSER_BACK:
      return "Back";
    case ui::VKEY_BROWSER_REFRESH:
      return "Refresh";
    case ui::VKEY_BROWSER_HOME:
      return "Home";
    case ui::VKEY_BROWSER_STOP:
      return "Stop";
    case ui::VKEY_BROWSER_FAVORITES:
      return "Favorites";
    case ui::VKEY_NEW:
      return "New";
    case ui::VKEY_CLOSE:
      return "Close";
    case ui::VKEY_BACK:
      return "Back";
    case ui::VKEY_DELETE:
      return "Delete";
    case ui::VKEY_MEDIA_PLAY_PAUSE:
      return "Play Pause";
    case ui::VKEY_MEDIA_PLAY:
      return "Play";
    case ui::VKEY_MEDIA_PAUSE:
      return "Pause";
    case ui::VKEY_VOLUME_MUTE:
      return "Mute";
    case ui::VKEY_TAB:
      return "Tab";
    case ui::VKEY_NEXT:
      return "Next";
    case ui::VKEY_PRIOR:
      return "Prev";
    case ui::VKEY_RETURN:
      return "Enter";
    case ui::VKEY_NUMPAD1:
      return "1";
    case ui::VKEY_NUMPAD2:
      return "2";
    case ui::VKEY_NUMPAD3:
      return "3";
    case ui::VKEY_NUMPAD4:
      return "4";
    case ui::VKEY_NUMPAD5:
      return "5";
    case ui::VKEY_NUMPAD6:
      return "6";
    case ui::VKEY_NUMPAD7:
      return "7";
    case ui::VKEY_NUMPAD8:
      return "8";
    case ui::VKEY_NUMPAD9:
      return "9";
    case ui::VKEY_NUMPAD0:
      return "0";
    case ui::VKEY_OEM_MINUS:
      return "-";
    case ui::VKEY_OEM_PLUS:
      return "+";
    case ui::VKEY_SPACE:
      return "Space";
    default:
      std::string result;
      result = toupper(ui::GetUnicodeCharacterFromXKeySym(code));
      return result;
  }
}
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
