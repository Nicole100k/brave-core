/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_CHOOSE_PREDICT_AD_EMBEDDINGS_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_CHOOSE_PREDICT_AD_EMBEDDINGS_H_

#include <iostream>
#include <vector>

#include "absl/types/optional.h"
#include "base/rand_util.h"
#include "bat/ads/internal/ads/serving/choose/eligible_ads_predictor_util.h"
#include "bat/ads/internal/ads/serving/eligible_ads/pacing/pacing.h"
#include "bat/ads/internal/base/numbers/number_util.h"
#include "bat/ads/internal/ml/data/vector_data.h"
#include "bat/ads/internal/processors/contextual/text_embedding/text_embedding_html_event_info.h"
#include "bat/ads/internal/processors/contextual/text_embedding/text_embedding_html_events.h"

namespace ads {

template <typename T>
void PredictAdEmbeddings(
    const targeting::UserModelInfo& user_model,
    const AdEventList& ad_events,
    const std::vector<T>& creative_ads,
    std::function<void(const absl::optional<T>)> callback) {
  DCHECK(!creative_ads.empty());

  const std::vector<T> paced_creative_ads = PaceCreativeAds(creative_ads);

  GetTextEmbeddingHtmlEventsFromDatabase(
      [=](const bool success,
          const TextEmbeddingHtmlEventList& text_embedding_html_events) {
        if (!success) {
          return;
        }

        const int text_embedding_html_event_count =
            text_embedding_html_events.size();
        std::cerr << "** Text Embedding Events Count: "
                  << text_embedding_html_event_count;

        std::vector<int> votes_registry;
        votes_registry.assign(creative_ads.size(), 0);
        for (const auto& text_embedding : text_embedding_html_events) {
          int max_idx = 0;
          float max_similarity = 0;
          for (const auto creative_ad : paced_creative_ads) {
            ml::VectorData ad_embedding = ml::VectorData(creative_ad.embedding);
            const ml::VectorData page_text_embedding =
                ml::VectorData(text_embedding.embedding);
            const float similarity_score =
                ad_embedding.ComputeSimilarity(page_text_embedding);

            if (similarity_score > max_similarity) {
              max_idx = std::find(paced_creative_ads.begin(),
                                  paced_creative_ads.end(), creative_ad) -
                        paced_creative_ads.begin();
              max_similarity = similarity_score;
            }
          }
          votes_registry[max_idx] += 1;
        }

        std::vector<double> probabilities;

        double normalizing_constant = 0.0;
        for (const auto& votes : votes_registry) {
          normalizing_constant += votes;
        }

        probabilities.reserve(votes_registry.size());
        for (const auto& votes : votes_registry) {
          probabilities.push_back(votes / normalizing_constant);
        }

        const double rand = base::RandDouble();
        double sum = 0;

        for (size_t i = 0; i < paced_creative_ads.size(); i++) {
          const T creative_ad = paced_creative_ads[i];
          const double probability = probabilities[i];
          sum += probability;

          if (DoubleIsLess(rand, sum)) {
            callback(creative_ad);
          }
        }
      });
}

}  // namespace ads

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_CHOOSE_PREDICT_AD_EMBEDDINGS_H_
