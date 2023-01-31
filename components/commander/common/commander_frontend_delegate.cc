// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/commander/common/commander_frontend_delegate.h"

namespace commander {
CommanderFrontendDelegate* CommanderFrontendDelegate::instance_ = nullptr;
CommanderFrontendDelegate* CommanderFrontendDelegate::Get() {
  return CommanderFrontendDelegate::instance_;
}
void CommanderFrontendDelegate::SetInstance(
    CommanderFrontendDelegate* instance) {
  instance_ = instance;
}
}  // namespace commander
