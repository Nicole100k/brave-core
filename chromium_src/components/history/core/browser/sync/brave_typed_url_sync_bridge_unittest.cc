/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

// Run all TypedURLSyncBridgeTest again but with kBraveSyncSendAllHistory
// feature enabled

#include "brave/components/history/core/browser/sync/brave_typed_url_sync_bridge.h"
#include "base/test/scoped_feature_list.h"
#include "brave/components/brave_sync/features.h"

#define BRAVE_SCOPED_FEATURE_LIST_DECLARE \
  base::test::ScopedFeatureList scoped_feature_list_;

#define BRAVE_SCOPED_FEATURE_LIST_INIT   \
  scoped_feature_list_.InitWithFeatures( \
      {brave_sync::features::kBraveSyncSendAllHistory}, {});

// Disable the original tests which fail when kBraveSyncSendAllHistory feature
// is enabled. The fixed versions of these tests are below.
#define DeleteLocalTypedUrlVisit DISABLED_DeleteLocalTypedUrlVisit
// See BraveTypedURLSyncBridgeTest.BraveExpireLocalTypedVisit
#define ExpireLocalTypedVisit DISABLED_ExpireLocalTypedVisit
// See BraveTypedURLSyncBridgeTest, BraveMaxVisitLocalTypedUrl
#define MaxVisitLocalTypedUrl DISABLED_MaxVisitLocalTypedUrlt
// See BraveTypedURLSyncBridgeTest.BraveSendAllVisitOverrideNoTypedVisits
#define NoTypedVisits DISABLED_NoTypedVisits
// See BraveTypedURLSyncBridgeTest.BraveThrottleVisitLocalTypedUrl
#define ThrottleVisitLocalTypedUrl DISABLED_ThrottleVisitLocalTypedUrl
// See BraveTypedURLSyncBridgeTest.BraveTooManyVisits
#define TooManyVisits DISABLED_TooManyVisits
// See BraveTypedURLSyncBridgeTest.BraveUpdateLocalTypedUrl
#define UpdateLocalTypedUrl DISABLED_UpdateLocalTypedUrl
// See BraveTypedURLSyncBridgeTest.BraveWriteTypedUrlSpecifics
#define WriteTypedUrlSpecifics DISABLED_WriteTypedUrlSpecifics

#define TypedURLSyncBridge BraveTypedURLSyncBridge
#define TypedURLSyncBridgeTest BraveTypedURLSyncBridgeTest
#include "src/components/history/core/browser/sync/typed_url_sync_bridge_unittest.cc"
#undef TypedURLSyncBridgeTest
#undef TypedURLSyncBridge

#undef WriteTypedUrlSpecifics
#undef UpdateLocalTypedUrl
#undef TooManyVisits
#undef ThrottleVisitLocalTypedUrl
#undef NoTypedVisits
#undef MaxVisitLocalTypedUrl
#undef ExpireLocalTypedVisit
#undef DeleteLocalTypedUrlVisit

namespace {

bool IsSendAllHistoryEnabled() {
  return base::FeatureList::IsEnabled(
      brave_sync::features::kBraveSyncSendAllHistory);
}

}  // namespace

namespace history {

// Create three visits, check RELOAD visit is NOT removed by
// WriteToTypedUrlSpecifics so it won't apply to sync DB.
TEST_F(BraveTypedURLSyncBridgeTest, BraveWriteTypedUrlSpecifics) {
  ASSERT_TRUE(IsSendAllHistoryEnabled());
  std::vector<VisitRow> visits;
  visits.push_back(CreateVisit(ui::PAGE_TRANSITION_TYPED, 1));
  visits.push_back(CreateVisit(ui::PAGE_TRANSITION_RELOAD, 2));
  visits.push_back(CreateVisit(ui::PAGE_TRANSITION_LINK, 3));
  URLRow url(MakeTypedUrlRow(kURL, kTitle, 0, 100, false, &visits));
  sync_pb::TypedUrlSpecifics typed_url;
  WriteToTypedUrlSpecifics(url, visits, &typed_url);
  // RELOAD visits should NOT be removed.
  EXPECT_EQ(4, typed_url.visits_size());
  EXPECT_EQ(typed_url.visit_transitions_size(), typed_url.visits_size());
  EXPECT_EQ(1, typed_url.visits(0));
  EXPECT_EQ(2, typed_url.visits(1));
  EXPECT_EQ(3, typed_url.visits(2));
  EXPECT_EQ(static_cast<int32_t>(ui::PAGE_TRANSITION_TYPED),
            typed_url.visit_transitions(0));
  EXPECT_EQ(static_cast<int32_t>(ui::PAGE_TRANSITION_RELOAD),
            typed_url.visit_transitions(1));
  EXPECT_EQ(static_cast<int32_t>(ui::PAGE_TRANSITION_LINK),
            typed_url.visit_transitions(2));
}

// This is re-done TypedURLSyncBridgeTest.NoTypedVisits test for
// the case when Brave's kBraveSyncSendAllHistory feature is enabled.
TEST_F(BraveTypedURLSyncBridgeTest, BraveSendAllVisitOverrideNoTypedVisits) {
  ASSERT_TRUE(IsSendAllHistoryEnabled());

  std::vector<VisitRow> visits;
  URLRow url(MakeTypedUrlRow(kURL, kTitle, 0, 1000, false, &visits));

  sync_pb::TypedUrlSpecifics typed_url;
  EXPECT_TRUE(WriteToTypedUrlSpecifics(url, visits, &typed_url));
  // Below is difference from TypedURLSyncBridgeTest.NoTypedVisits:
  // URLs without typed URL visits, but with link transition should be written
  // to specifics.
  EXPECT_EQ(1, typed_url.visits_size());
}

// Create 101 visits, check WriteToTypedUrlSpecifics will only keep 100 visits.
TEST_F(BraveTypedURLSyncBridgeTest, BraveTooManyVisits) {
  ASSERT_TRUE(IsSendAllHistoryEnabled());

  std::vector<VisitRow> visits;
  int64_t timestamp = 1000;
  visits.push_back(CreateVisit(ui::PAGE_TRANSITION_TYPED, timestamp++));
  for (int i = 0; i < 100; ++i) {
    visits.push_back(CreateVisit(ui::PAGE_TRANSITION_LINK, timestamp++));
  }

  // |MakeTypedUrlRow| adds one visit PAGE_TRANSITION_RELOAD, so will have to
  // adjust test expectation, as that reload will not be removed by
  // |WriteToTypedUrlSpecifics|
  URLRow url(MakeTypedUrlRow(kURL, kTitle, 0, timestamp++, false, &visits));
  sync_pb::TypedUrlSpecifics typed_url;
  WriteToTypedUrlSpecifics(url, visits, &typed_url);
  // # visits should be capped at 100.
  EXPECT_EQ(100, typed_url.visits_size());
  EXPECT_EQ(typed_url.visit_transitions_size(), typed_url.visits_size());
  EXPECT_EQ(1000, typed_url.visits(0));

  // This is adjusted to 1003, because with kSendAllHistoryEnabled feature
  // WriteToTypedUrlSpecifics did not removed RELOAD visit, and therefore
  // to fit into 100 visits, we had to delete 1001 and 1002 visits, so
  // expecting 1003 at index 1
  EXPECT_EQ(1003, typed_url.visits(1));
  EXPECT_EQ(static_cast<int32_t>(ui::PAGE_TRANSITION_TYPED),
            typed_url.visit_transitions(0));
  EXPECT_EQ(static_cast<int32_t>(ui::PAGE_TRANSITION_LINK),
            typed_url.visit_transitions(1));
  EXPECT_EQ(static_cast<int32_t>(ui::PAGE_TRANSITION_RELOAD),
            typed_url.visit_transitions(99));
}

// Saturate the visits for a typed url with both TYPED and LINK navigations.
// Check that no more than kMaxTypedURLVisits are synced, and that LINK visits
// are NOT dropped.
TEST_F(BraveTypedURLSyncBridgeTest, BraveMaxVisitLocalTypedUrl) {
  ASSERT_TRUE(IsSendAllHistoryEnabled());

  std::vector<URLRow> url_rows;
  std::vector<std::vector<VisitRow>> visit_vectors;
  std::vector<std::string> urls;
  urls.push_back(kURL);

  // BuildAndPushLocalChanges => MakeTypedUrlRow creates RELOAD visit
  // which is not ignored with kSendAllHistoryEnabled feature. So it
  // gets sent and expectation time is adjusted to 1
  EXPECT_CALL(mock_processor_, Put).Times(1);
  StartSyncing(std::vector<TypedUrlSpecifics>());
  BuildAndPushLocalChanges(0, 1, urls, &url_rows, &visit_vectors);

  URLRow url_row = url_rows.front();
  std::vector<VisitRow> visits;

  // Add `kMaxTypedUrlVisits` + 10 visits to the url. The 10 oldest
  // non-typed visits are expected to be skipped.
  int i = 1;
  for (; i <= kMaxTypedUrlVisits - 20; ++i) {
    AddNewestVisit(ui::PAGE_TRANSITION_TYPED, i, &url_row, &visits);
  }
  for (; i <= kMaxTypedUrlVisits; ++i) {
    AddNewestVisit(ui::PAGE_TRANSITION_LINK, i, &url_row, &visits);
  }
  for (; i <= kMaxTypedUrlVisits + 10; ++i) {
    AddNewestVisit(ui::PAGE_TRANSITION_TYPED, i, &url_row, &visits);
  }

  fake_history_backend_->SetVisitsForUrl(&url_row, visits);

  // Notify typed url sync service of typed visit.
  EntityData entity_data;
  EXPECT_CALL(mock_processor_, Put(GetStorageKey(kURL), _, _))
      .WillOnce(SaveArgPointeeMove<1>(&entity_data));
  bridge()->OnURLVisited(fake_history_backend_.get(), url_row, visits.front());

  const sync_pb::TypedUrlSpecifics& url_specifics =
      entity_data.specifics.typed_url();
  ASSERT_EQ(kMaxTypedUrlVisits, url_specifics.visits_size());

  // Check that each visit has been translated/communicated correctly.
  // Note that the specifics records visits in chronological order, and the
  // visits from the db are in reverse chronological order.
  int num_typed_visits_synced = 0;
  int num_other_visits_synced = 0;
  int r = url_specifics.visits_size() - 1;
  for (int j = 0; j < url_specifics.visits_size(); ++j, --r) {
    if (url_specifics.visit_transitions(j) ==
        static_cast<int32_t>(ui::PAGE_TRANSITION_TYPED)) {
      ++num_typed_visits_synced;
    } else {
      ++num_other_visits_synced;
    }
  }
  EXPECT_EQ(kMaxTypedUrlVisits - 10, num_typed_visits_synced);
  EXPECT_EQ(10, num_other_visits_synced);
}

// Expire the last local typed visit for a URL (with some non-typed visits
// remaining). This results in the sync entity getting untracked. This has only
// impact on local store (metadata in the db and in-memory maps), nothing gets
// synced up.
TEST_F(BraveTypedURLSyncBridgeTest, BraveExpireLocalTypedVisit) {
  ASSERT_TRUE(IsSendAllHistoryEnabled());
  StartSyncing(std::vector<TypedUrlSpecifics>());

  // Add two URLs into the history db and notify the bridge to get it synced up
  // and thus also metadata written into the DB.
  std::vector<VisitRow> visits1, visits2;
  URLRow row1 = MakeTypedUrlRowWithTwoVisits(kURL, kTitle, /*typed_visit=*/2,
                                             /*reload_visit=*/5, &visits1);
  URLRow row2 = MakeTypedUrlRow(kURL2, kTitle2, /*typed_count=*/1,
                                /*last_visit=*/4, /*hidden=*/false, &visits2);
  fake_history_backend_->SetVisitsForUrl(&row1, visits1);
  fake_history_backend_->SetVisitsForUrl(&row2, visits2);

  // MakeTypedUrlRow creates RELOAD visit which is not ignored with
  // kSendAllHistoryEnabled feature. So it
  // gets sent and expectation times is adjusted 2u=>3u
  EXPECT_CALL(mock_processor_,
              Put(IsValidStorageKey(), Pointee(HasTypedUrlInSpecifics()), _))
      .Times(3u)
      .WillRepeatedly(StoreMetadata);
  bridge()->OnURLsModified(fake_history_backend_.get(), {row1, row2},
                           /*is_from_expiration=*/false);

  std::string storage_key1 = GetStorageKey(kURL);
  std::string storage_key2 = GetStorageKey(kURL2);
  EXPECT_THAT(GetAllSyncMetadataKeys(),
              UnorderedElementsAre(storage_key1, storage_key2));

  // Simulate expiration of all visits before time 3.
  fake_history_backend_->ExpireHistoryBeforeForTesting(SinceEpoch(3));
  URLRow row1_updated;
  ASSERT_TRUE(fake_history_backend_->GetURL(GURL(kURL), &row1_updated));
  EXPECT_EQ(row1_updated.typed_count(), 0);
  EXPECT_NE(row1_updated.last_visit(), base::Time());

  // Notify typed url sync service of these URLs getting expired (it does not
  // matter that we pass in the old version of row1, the bridge will fix it up).
  EXPECT_CALL(mock_processor_, Delete).Times(0);
  // OnURLsModified => UpdateSyncFromLocal => HasTypedUrl gives true with
  // kSendAllHistoryEnabled So, expiration branch of ExpireMetadataForURL is not
  // invoked and UntrackEntityForStorageKey also doesn't get invoked. Modifying
  // to '.Times(0)' to respect kSendAllHistoryEnabled feature
  EXPECT_CALL(mock_processor_, UntrackEntityForStorageKey(storage_key1))
      .Times(0);
  bridge()->OnURLsModified(fake_history_backend_.get(), {row1},
                           /*is_from_expiration=*/true);

  // As per comment above, due to existing RELOAD visit, which wasn't purged
  // with kSendAllHistoryEnabled feature enabled, nothing gets removed.
  // So expecting to have both storage_key1 and storage_key2 be in storage
  EXPECT_THAT(GetAllSyncMetadataKeys(),
              UnorderedElementsAre(storage_key1, storage_key2));
}

// Update a local typed URL that is already synced. Check that sync is sent an
// UPDATE for the existing url, and RELOAD visits are also synced under
// kSendAllHistoryEnabled flag.
TEST_F(BraveTypedURLSyncBridgeTest, BraveUpdateLocalTypedUrl) {
  ASSERT_TRUE(IsSendAllHistoryEnabled());
  std::vector<URLRow> url_rows;
  std::vector<std::vector<VisitRow>> visit_vectors;
  std::vector<std::string> urls;
  urls.push_back(kURL);

  StartSyncing(std::vector<TypedUrlSpecifics>());

  // Update the URL row, adding another typed visit to the visit vector.
  std::vector<URLRow> changed_urls;
  std::vector<VisitRow> visits;
  URLRow url_row = MakeTypedUrlRow(kURL, kTitle, 1, 3, false, &visits);
  AddNewestVisit(ui::PAGE_TRANSITION_TYPED, 7, &url_row, &visits);
  AddNewestVisit(ui::PAGE_TRANSITION_RELOAD, 8, &url_row, &visits);
  AddNewestVisit(ui::PAGE_TRANSITION_LINK, 9, &url_row, &visits);
  fake_history_backend_->SetVisitsForUrl(&url_row, visits);
  changed_urls.push_back(url_row);

  // Notify typed url sync service of the update.
  EntityData entity_data;
  EXPECT_CALL(mock_processor_, Put(GetStorageKey(kURL), _, _))
      .WillOnce(SaveArgPointeeMove<1>(&entity_data));
  bridge()->OnURLsModified(fake_history_backend_.get(), changed_urls,
                           /*is_from_expiration=*/false);

  const sync_pb::TypedUrlSpecifics& url_specifics =
      entity_data.specifics.typed_url();
  EXPECT_TRUE(URLsEqual(url_row, url_specifics));
  // Adjusting visits_size because RELOAD visit is not deleted with
  // kSendAllHistoryEnabled feature
  ASSERT_EQ(4, url_specifics.visits_size());

  // Check that each visit has been translated/communicated correctly.
  // Note that the specifics record visits in chronological order, and the
  // visits from the db are in reverse chronological order.
  EXPECT_EQ(visits[0].visit_time.ToDeltaSinceWindowsEpoch().InMicroseconds(),
            url_specifics.visits(3));
  EXPECT_EQ(static_cast<const int>(visits[0].transition),
            url_specifics.visit_transitions(3));

  // The extra visit in compare to the original test is RELOAD
  EXPECT_EQ(static_cast<const int>(ui::PAGE_TRANSITION_RELOAD),
            url_specifics.visit_transitions(2));
  EXPECT_EQ(visits[1].visit_time.ToDeltaSinceWindowsEpoch().InMicroseconds(),
            url_specifics.visits(2));
  EXPECT_EQ(static_cast<const int>(visits[1].transition),
            url_specifics.visit_transitions(2));

  EXPECT_EQ(visits[2].visit_time.ToDeltaSinceWindowsEpoch().InMicroseconds(),
            url_specifics.visits(1));
  EXPECT_EQ(static_cast<const int>(visits[2].transition),
            url_specifics.visit_transitions(1));
  EXPECT_EQ(visits[3].visit_time.ToDeltaSinceWindowsEpoch().InMicroseconds(),
            url_specifics.visits(0));
  EXPECT_EQ(static_cast<const int>(visits[3].transition),
            url_specifics.visit_transitions(0));
}

// Add enough visits to trigger throttling of updates to a typed url. Check that
// sync does not receive an update until the proper throttle interval has been
// reached.
TEST_F(BraveTypedURLSyncBridgeTest, BraveThrottleVisitLocalTypedUrl) {
  ASSERT_TRUE(IsSendAllHistoryEnabled());
  std::vector<URLRow> url_rows;
  std::vector<std::vector<VisitRow>> visit_vectors;
  std::vector<std::string> urls;
  urls.push_back(kURL);

  // With kSendAllHistoryEnabled feature enabled, at
  // BuildAndPushLocalChanges => OnURLsModified => UpdateSyncFromLocal
  // HasTypedUrl gives true  because there is one RELOAD visits which under that
  // feature on is treated as TYPED_URL, so must be sent to processor.
  EXPECT_CALL(mock_processor_, Put).Times(1);
  StartSyncing(std::vector<TypedUrlSpecifics>());
  BuildAndPushLocalChanges(0, 1, urls, &url_rows, &visit_vectors);

  URLRow url_row = url_rows.front();
  std::vector<VisitRow> visits;

  // Add enough visits to the url so that typed count is above the throttle
  // limit, and not right on the interval that gets synced.
  int i = 1;
  for (; i < bridge()->GetSendAllFlagVisitThrottleThreshold() +
                 bridge()->GetSendAllFlagVisitThrottleMultiple() / 2;
       ++i) {
    AddNewestVisit(ui::PAGE_TRANSITION_TYPED, i, &url_row, &visits);
  }
  fake_history_backend_->SetVisitsForUrl(&url_row, visits);

  // Notify typed url sync service of typed visit.
  bridge()->OnURLVisited(fake_history_backend_.get(), url_row, visits.front());

  visits.clear();
  for (; i % bridge()->GetSendAllFlagVisitThrottleMultiple() != 1; ++i) {
    AddNewestVisit(ui::PAGE_TRANSITION_TYPED, i, &url_row, &visits);
  }
  --i;  // Account for the increment before the condition ends.
  // Compensate RELOAD visit wich is ommitted in original test when
  // kSendAllHistoryEnabled is not enabled
  i++;
  fake_history_backend_->SetVisitsForUrl(&url_row, visits);

  // Notify typed url sync service of typed visit.
  EntityData entity_data;
  EXPECT_CALL(mock_processor_, Put(GetStorageKey(kURL), _, _))
      .WillOnce(SaveArgPointeeMove<1>(&entity_data));
  bridge()->OnURLVisited(fake_history_backend_.get(), url_row, visits.front());

  ASSERT_EQ(i, entity_data.specifics.typed_url().visits_size());
}

URLRow MakeUrlRow(int visit_count, int typed_count) {
  URLRow urlRow;
  urlRow.set_visit_count(visit_count);
  urlRow.set_typed_count(typed_count);
  return urlRow;
}

TEST_F(BraveTypedURLSyncBridgeTest, BraveShouldSyncVisit) {
  ASSERT_TRUE(IsSendAllHistoryEnabled());

  EXPECT_TRUE(
      bridge()->ShouldSyncVisit(MakeUrlRow(1, 0), ui::PAGE_TRANSITION_LINK));
  EXPECT_TRUE(
      bridge()->ShouldSyncVisit(MakeUrlRow(1, 0), ui::PAGE_TRANSITION_TYPED));
  EXPECT_TRUE(
      bridge()->ShouldSyncVisit(MakeUrlRow(20, 0), ui::PAGE_TRANSITION_LINK));
  EXPECT_FALSE(
      bridge()->ShouldSyncVisit(MakeUrlRow(21, 0), ui::PAGE_TRANSITION_LINK));
  EXPECT_TRUE(
      bridge()->ShouldSyncVisit(MakeUrlRow(30, 0), ui::PAGE_TRANSITION_LINK));

  {
    base::test::ScopedFeatureList scoped_feature_list2;
    scoped_feature_list2.InitWithFeatures(
        {}, {brave_sync::features::kBraveSyncSendAllHistory});
    EXPECT_FALSE(
        bridge()->ShouldSyncVisit(MakeUrlRow(1, 0), ui::PAGE_TRANSITION_LINK));
    EXPECT_TRUE(
        bridge()->ShouldSyncVisit(MakeUrlRow(1, 1), ui::PAGE_TRANSITION_TYPED));
    EXPECT_FALSE(bridge()->ShouldSyncVisit(MakeUrlRow(20, 20),
                                           ui::PAGE_TRANSITION_LINK));
    EXPECT_TRUE(bridge()->ShouldSyncVisit(MakeUrlRow(20, 20),
                                          ui::PAGE_TRANSITION_TYPED));
  }
}

}  // namespace history
