/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "components/history/core/browser/sync/typed_url_sync_bridge.h"

#include "brave/components/brave_sync/features.h"
#include "ui/base/page_transition_types.h"

namespace {

bool IsSendAllHistoryEnabled() {
  return base::FeatureList::IsEnabled(
      brave_sync::features::kBraveSyncSendAllHistory);
}

}  // namespace

namespace ui {

static bool PageTransitionCoreTypeIs_BraveImpl(PageTransition lhs,
                                               PageTransition rhs) {
  if (IsSendAllHistoryEnabled() &&
      PageTransitionCoreTypeIs(rhs, ui::PAGE_TRANSITION_RELOAD)) {
    // At TypedURLSyncBridge::WriteToTypedUrlSpecifics when syncing all
    // history, don't ignore reload transitions.
    return false;
  }
  return PageTransitionCoreTypeIs(lhs, rhs);
}

}  // namespace ui

#define BRAVE_TYPED_URL_SYNC_BRIDGE_ON_URL_VISITED_REPLACE_SHOULD_SYNC_VISIT \
  if (!ShouldSyncVisit(url_row, visit_row.transition)) {                     \
    return;                                                                  \
  }                                                                          \
  if (false)

#define PageTransitionCoreTypeIs PageTransitionCoreTypeIs_BraveImpl

#include "src/components/history/core/browser/sync/typed_url_sync_bridge.cc"

#undef PageTransitionCoreTypeIs
#undef BRAVE_TYPED_URL_SYNC_BRIDGE_ON_URL_VISITED_REPLACE_SHOULD_SYNC_VISIT

namespace history {

// static
bool TypedURLSyncBridge::HasTypedUrl(const std::vector<VisitRow>& visits) {
  if (IsSendAllHistoryEnabled()) {
    // When there are no visits, we must return false. Otherwise
    // TypedURLSyncBridge will try to send data to sync
    return !visits.empty();
  }
  return ::history::HasTypedUrl(visits);
}

}  // namespace history
