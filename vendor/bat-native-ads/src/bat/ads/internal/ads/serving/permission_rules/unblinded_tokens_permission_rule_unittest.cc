/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/ads/serving/permission_rules/unblinded_tokens_permission_rule.h"

#include "bat/ads/internal/common/unittest/unittest_base.h"
#include "bat/ads/internal/privacy/tokens/unblinded_tokens/unblinded_tokens_unittest_util.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace ads {

class BatAdsUnblindedTokensPermissionRuleTest : public UnitTestBase {};

TEST_F(BatAdsUnblindedTokensPermissionRuleTest, AllowAdIfDoesNotExceedCap) {
  // Arrange
  privacy::BuildAndSetUnblindedTokens(/*count*/ 10);

  // Act
  UnblindedTokensPermissionRule permission_rule;
  const bool is_allowed = permission_rule.ShouldAllow();

  // Assert
  EXPECT_TRUE(is_allowed);
}

TEST_F(BatAdsUnblindedTokensPermissionRuleTest,
       DoNotAllowAdIfNoUnblindedTokens) {
  // Arrange

  // Act
  UnblindedTokensPermissionRule permission_rule;
  const bool is_allowed = permission_rule.ShouldAllow();

  // Assert
  EXPECT_FALSE(is_allowed);
}

TEST_F(BatAdsUnblindedTokensPermissionRuleTest, DoNotAllowAdIfExceedsCap) {
  // Arrange
  privacy::BuildAndSetUnblindedTokens(/*count*/ 9);

  // Act
  UnblindedTokensPermissionRule permission_rule;
  const bool is_allowed = permission_rule.ShouldAllow();

  // Assert
  EXPECT_FALSE(is_allowed);
}

}  // namespace ads
