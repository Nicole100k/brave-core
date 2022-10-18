/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/ads/serving/targeting/user_model_builder.h"

#include "bat/ads/internal/ads/serving/targeting/models/behavioral/bandits/epsilon_greedy_bandit_model.h"
#include "bat/ads/internal/ads/serving/targeting/models/behavioral/purchase_intent/purchase_intent_model.h"
#include "bat/ads/internal/ads/serving/targeting/models/contextual/text_classification/text_classification_model.h"
#include "bat/ads/internal/ads/serving/targeting/user_model_info.h"
#include "bat/ads/internal/base/logging_util.h"
#include "bat/ads/internal/features/epsilon_greedy_bandit_features.h"
#include "bat/ads/internal/features/purchase_intent_features.h"
#include "bat/ads/internal/features/text_classification_features.h"
#include "bat/ads/internal/processors/contextual/text_embedding/text_embedding_html_event_info.h"
#include "bat/ads/internal/processors/contextual/text_embedding/text_embedding_html_events.h"

namespace ads::targeting {

void BuildUserModel(GetUserModelCallback callback) {
  UserModelInfo user_model;

  if (features::IsTextClassificationEnabled()) {
    const model::TextClassification text_classification_model;
    user_model.interest_segments = text_classification_model.GetSegments();
  }

  if (features::IsEpsilonGreedyBanditEnabled()) {
    const model::EpsilonGreedyBandit epsilon_greedy_bandit_model;
    user_model.latent_interest_segments =
        epsilon_greedy_bandit_model.GetSegments();
  }

  if (features::IsPurchaseIntentEnabled()) {
    const model::PurchaseIntent purchase_intent_model;
    user_model.purchase_intent_segments = purchase_intent_model.GetSegments();
  }

  GetTextEmbeddingHtmlEventsFromDatabase(
      [=](const bool success, const TextEmbeddingHtmlEventList&
                                  text_embedding_html_events) mutable {
        if (!success) {
          BLOG(1, "Failed to get text embedding events");
          callback(user_model);
          return;
        }

        user_model.text_embedding_html_events = text_embedding_html_events;

        callback(user_model);
      });
}

}  // namespace ads::targeting
