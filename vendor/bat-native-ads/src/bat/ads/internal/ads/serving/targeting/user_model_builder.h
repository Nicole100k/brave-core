/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_TARGETING_USER_MODEL_BUILDER_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_TARGETING_USER_MODEL_BUILDER_H_

#include <functional>

#include "base/bind.h"
#include "bat/ads/internal/processors/contextual/text_embedding/text_embedding_html_event_info.h"

namespace ads::targeting {

struct UserModelInfo;

using GetUserModelCallback =
    base::OnceCallback<void(const targeting::UserModelInfo& user_model)>;

void BuildUserModel(GetUserModelCallback callback);
void OnGetTextEmbeddingHtmlEvents(
    UserModelInfo& user_model,
    GetUserModelCallback callback,
    bool success,
    const TextEmbeddingHtmlEventList& text_embedding_html_events);

}  // namespace ads::targeting

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_TARGETING_USER_MODEL_BUILDER_H_
