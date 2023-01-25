/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/android/speedreader/features.h"

#include "base/feature_list.h"

namespace speedreader {
namespace features {

BASE_FEATURE(kBraveAndroidSpeedReader,
             "BraveAndroidSpeedReader",
             base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace features
}  // namespace speedreader
