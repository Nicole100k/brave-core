// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/commander/common/commander_url.h"

#include <string>
#include <vector>

#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"
#include "base/unguessable_token.h"

namespace commander {
namespace {
std::string GetScheme() {
  // For the commander urls, we generate an unguessable scheme so that these
  // commands can't be triggered unless you already know the token.
  static std::string scheme = base::ToLowerASCII(
      "brave-commands-" + base::UnguessableToken::Create().ToString());
  return scheme;
}
}  // namespace

GURL GetCommandURL(uint32_t command_index, uint32_t result_set_id) {
  return GURL(GetScheme() + "://" + base::NumberToString(command_index) + "/" +
              base::NumberToString(result_set_id));
}

bool TryParseCommandURL(const GURL& url,
                        uint32_t* command_index,
                        uint32_t* result_set_id) {
  if (!url.SchemeIs(GetScheme())) {
    return false;
  }

  std::vector<std::string> parts = base::SplitString(
      url.path(), "/", base::KEEP_WHITESPACE, base::SPLIT_WANT_NONEMPTY);
  return parts.size() == 2 && base::StringToUint(parts[0], command_index) &&
         base::StringToUint(parts[1], result_set_id);
}

}  // namespace commander
