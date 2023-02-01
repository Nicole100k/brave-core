// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_URL_H_
#define BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_URL_H_

#include "url/gurl.h"

namespace commander {
GURL GetCommandURL(uint32_t command_index, uint32_t result_set_id);
bool TryParseCommandURL(const GURL& url,
                        uint32_t* command_index,
                        uint32_t* result_set_id);
}  // namespace commander

#endif  // BRAVE_COMPONENTS_COMMANDER_COMMON_COMMANDER_URL_H_
