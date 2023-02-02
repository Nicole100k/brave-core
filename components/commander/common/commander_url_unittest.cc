// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/commander/common/commander_url.h"

#include "base/strings/string_util.h"
#include "testing/gtest/include/gtest/gtest.h"

TEST(BraveCommander, UrlsShouldRoundTrip) {
  uint32_t result_set_id = 1023;
  uint32_t command_index = 459913;

  auto url = commander::GetCommandURL(command_index, result_set_id);

  uint32_t parsed_result_set_id;
  uint32_t parsed_command_index;

  ASSERT_TRUE(commander::TryParseCommandURL(url, &parsed_command_index,
                                            &parsed_result_set_id));
  EXPECT_EQ(result_set_id, parsed_result_set_id);
  EXPECT_EQ(command_index, parsed_command_index);
}
