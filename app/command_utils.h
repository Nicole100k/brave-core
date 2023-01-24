
// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BUILD_GENERATE_COMMAND_METADATA_H_
#define BRAVE_BUILD_GENERATE_COMMAND_METADATA_H_

#include <string>
#include <vector>

namespace shortcuts {

std::vector<uint16_t> GetCommands(); 
std::string GetCommandName(int command_id);
}

#endif  // BRAVE_BUILD_GENERATE_COMMAND_METADATA_H_
  