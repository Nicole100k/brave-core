// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/commander/commander_throttle.h"

#include <cstdint>
#include <string>
#include <vector>

#include "base/functional/bind.h"
#include "base/functional/callback_forward.h"
#include "base/location.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "base/task/post_job.h"
#include "base/task/single_thread_task_runner.h"
#include "base/task/task_traits.h"
#include "base/task/thread_pool.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/commander/commander.h"
#include "chrome/browser/ui/commander/commander_backend.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/navigation_throttle.h"

const char kCommanderThrottleName[] = "CommanderThrottle";

CommanderThrottle::CommanderThrottle(content::NavigationHandle* handle)
    : content::NavigationThrottle(handle) {}

CommanderThrottle::~CommanderThrottle() = default;

content::NavigationThrottle::ThrottleCheckResult
CommanderThrottle::WillStartRequest() {
  if (navigation_handle()->GetURL().SchemeIs("brave-command")) {
    auto url = navigation_handle()->GetURL();
    std::vector<std::string> parts = base::SplitString(
        url.path(), "/", base::KEEP_WHITESPACE, base::SPLIT_WANT_NONEMPTY);
    uint32_t session_id;
    uint32_t command_index;
    if (parts.size() >= 2 && base::StringToUint(parts[0], &session_id) &&
        base::StringToUint(parts[1], &command_index)) {
      base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
          FROM_HERE, base::BindOnce(
                         [](int session_id, int command_index) {
                           auto* commander = commander::Commander::Get();
                           commander->backend()->OnCommandSelected(
                               command_index, session_id);
                         },
                         session_id, command_index));
    }
    return ThrottleCheckResult(ThrottleAction::CANCEL_AND_IGNORE);
  }
  return ThrottleCheckResult(ThrottleAction::PROCEED);
}

const char* CommanderThrottle::GetNameForLogging() {
  return kCommanderThrottleName;
}
