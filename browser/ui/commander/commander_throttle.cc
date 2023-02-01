// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/commander/commander_throttle.h"

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
#include "brave/components/commander/common/commander_url.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/commander/commander.h"
#include "chrome/browser/ui/commander/commander_backend.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/navigation_throttle.h"

namespace commander {
CommanderThrottle::CommanderThrottle(content::NavigationHandle* handle)
    : content::NavigationThrottle(handle) {}

CommanderThrottle::~CommanderThrottle() = default;

content::NavigationThrottle::ThrottleCheckResult
CommanderThrottle::WillStartRequest() {
  // Don't handle renderer initiated navigations, we don't want them to be able
  // to trigger commands.
  // Note: As an additional protection, commander URLs have an
  // base::UnguessableToken which needs to be set correctly in order to work
  // properly.
  if (navigation_handle()->IsRendererInitiated()) {
    return ThrottleCheckResult(ThrottleAction::PROCEED);
  }

  uint32_t command_index;
  uint32_t result_set_id;
  if (commander::TryParseCommandURL(navigation_handle()->GetURL(),
                                    &command_index, &result_set_id)) {
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
        FROM_HERE, base::BindOnce(
                       [](int command_index, int result_set_id) {
                         auto* commander = commander::Commander::Get();
                         commander->backend()->OnCommandSelected(command_index,
                                                                 result_set_id);
                       },
                       command_index, result_set_id));
    return ThrottleCheckResult(ThrottleAction::CANCEL_AND_IGNORE);
  }
  return ThrottleCheckResult(ThrottleAction::PROCEED);
}

const char* CommanderThrottle::GetNameForLogging() {
  return "CommanderThrottle";
}
}  // namespace commander
