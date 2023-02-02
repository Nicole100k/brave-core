// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/omnibox/browser/brave_omnibox_edit_model.h"

#include "brave/components/commander/common/commander_frontend_delegate.h"
#include "brave/components/commander/common/commander_url.h"
#include "components/omnibox/browser/omnibox_edit_model.h"

BraveOmniboxEditModel::~BraveOmniboxEditModel() = default;

void BraveOmniboxEditModel::OpenMatch(
    AutocompleteMatch match,
    WindowOpenDisposition disposition,
    const GURL& alternate_nav_url,
    const std::u16string& pasted_text,
    size_t index,
    base::TimeTicks match_selection_timestamp) {
  uint32_t command_index;
  uint32_t result_set_id;
  if (commander::TryParseCommandURL(match.destination_url, &command_index,
                                    &result_set_id)) {
    commander::CommanderFrontendDelegate::Get()->SelectCommand(command_index,
                                                               result_set_id);
    return;
  }
  OmniboxEditModel::OpenMatch(match, disposition, alternate_nav_url,
                              pasted_text, index, match_selection_timestamp);
}
