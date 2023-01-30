// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_COMMANDER_COMMANDER_H_
#define BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_COMMANDER_COMMANDER_H_

#include "chrome/browser/ui/commander/commander_backend.h"
#include "chrome/browser/ui/commander/commander_frontend.h"

#define Initialize                                          \
  virtual Initialize();                                     \
  CommanderBackend* backend() { return backend_.get(); }    \
  CommanderFrontend* frontend() { return frontend_.get(); } \
  void Initialize_Unused

#include "src/chrome/browser/ui/commander/commander.h"

#undef Initialize

#endif  // BRAVE_CHROMIUM_SRC_CHROME_BROWSER_UI_COMMANDER_COMMANDER_H_
