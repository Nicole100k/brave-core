// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/omnibox/browser/commander_provider.h"

#include <cmath>
#include <string>
#include <utility>

#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "brave/components/commander/common/commander_frontend_delegate.h"
#include "brave/components/commander/common/commander_model.h"
#include "brave/components/commander/common/commander_url.h"
#include "brave/components/commander/common/constants.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/autocomplete_match_type.h"
#include "components/omnibox/browser/autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_provider_listener.h"

namespace commander {
CommanderProvider::CommanderProvider(AutocompleteProviderClient* client,
                                     AutocompleteProviderListener* listener)
    : AutocompleteProvider(AutocompleteProvider::TYPE_BRAVE_COMMANDER) {
  if (listener) {
    AddListener(listener);
  }

  auto* delegate = commander::CommanderFrontendDelegate::Get();
  if (delegate) {
    delegate->AddObserver(this);
  }
}

CommanderProvider::~CommanderProvider() {
  auto* delegate = commander::CommanderFrontendDelegate::Get();
  if (delegate) {
    delegate->RemoveObserver(this);
  }
}

void CommanderProvider::Start(const AutocompleteInput& input,
                              bool minimal_changes) {
  last_input_ = input.text();

  Stop(true, false);
  if (base::StartsWith(input.text(), commander::kCommandPrefix)) {
    std::u16string text(base::TrimWhitespace(
        input.text().substr(2), base::TrimPositions::TRIM_LEADING));
    auto* delegate = commander::CommanderFrontendDelegate::Get();
    if (!IsInObserverList()) {
      delegate->AddObserver(this);
    }
    delegate->SetText(text);
  }
}

void CommanderProvider::OnModelUpdated(const commander::CommanderModel& model) {
  matches_.clear();
  if (model.action == commander::CommanderModel::kPrompt) {
    current_prompt_ = model.prompt_text;
  } else if (model.action == commander::CommanderModel::kClose) {
    current_prompt_ = u"";
    return;
  }

  int rank = 10000;
  for (uint32_t i = 0; i < model.items.size(); ++i) {
    const auto& option = model.items[i];
    AutocompleteMatch match(this, rank--, false,
                            AutocompleteMatchType::BOOKMARK_TITLE);
    // This is neat but it would be nice if we could always show it instead of
    // only when we have a result selected.
    match.contents = option.annotation;
    match.additional_text = current_prompt_;
    if (!option.annotation.empty()) {
      match.contents_class = {
          ACMatchClassification(0, ACMatchClassification::DIM)};
    }
    match.description =
        commander::kCommandPrefix + std::u16string(u" ") + option.title;
    match.allowed_to_be_default_match = true;
    match.swap_contents_and_description = true;
    // We don't want to change the prompt at all while the user is going through
    // their options.
    match.fill_into_edit = last_input_;
    match.destination_url = commander::GetCommandURL(i, model.result_set_id);
    match.description_class = {
        ACMatchClassification(0, ACMatchClassification::DIM),
        ACMatchClassification(2, ACMatchClassification::MATCH)};
    matches_.push_back(match);
  }

  NotifyListeners(true);
}
}  // namespace commander
