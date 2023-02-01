// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BROWSER_UI_COMMANDER_COMMANDER_THROTTLE_H_
#define BRAVE_BROWSER_UI_COMMANDER_COMMANDER_THROTTLE_H_

#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/navigation_throttle.h"

namespace commander {
class CommanderThrottle : public content::NavigationThrottle {
 public:
  explicit CommanderThrottle(content::NavigationHandle* handle);
  ~CommanderThrottle() override;

  // content::NavigationThrottle:
  ThrottleCheckResult WillStartRequest() override;
  const char* GetNameForLogging() override;
};
}  // namespace commander

#endif  // BRAVE_BROWSER_UI_COMMANDER_COMMANDER_THROTTLE_H_
