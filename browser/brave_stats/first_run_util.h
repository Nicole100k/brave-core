/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_BRAVE_STATS_FIRST_RUN_UTIL_H_
#define BRAVE_BROWSER_BRAVE_STATS_FIRST_RUN_UTIL_H_

#include "base/time/time.h"
#include "components/prefs/pref_service.h"

namespace brave_stats {

base::Time GetFirstRunTime(PrefService* local_state);

}  // namespace brave_stats

#endif  // BRAVE_BROWSER_BRAVE_STATS_FIRST_RUN_UTIL_H_
