// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_COMMANDER_COMMANDER_FRONTEND_H_
#define BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_COMMANDER_COMMANDER_FRONTEND_H_

#define Create                       \
  Create(CommanderBackend* backend); \
  std::unique_ptr<CommanderFrontend> Create_Unused

#include "src/chrome/browser/ui/commander/commander_frontend.h"

#undef Create

#endif  // BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_COMMANDER_COMMANDER_FRONTEND_H_
