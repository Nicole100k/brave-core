/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_P3A_BRAVE_P3A_SCHEDULER_H_
#define BRAVE_COMPONENTS_P3A_BRAVE_P3A_SCHEDULER_H_

#include "base/callback_forward.h"
#include "components/metrics/metrics_scheduler.h"

namespace brave {

// Handles scheduling of metric uploads/STAR metric preparation.
// Will callback to BraveP3AMessageManager on a given interval.
class BraveP3AScheduler : public metrics::MetricsScheduler {
 public:
  explicit BraveP3AScheduler(const base::RepeatingClosure& upload_callback,
                             bool randomize_upload_interval,
                             base::TimeDelta average_upload_interval);
  BraveP3AScheduler(const BraveP3AScheduler&) = delete;
  BraveP3AScheduler& operator=(const BraveP3AScheduler&) = delete;
  ~BraveP3AScheduler() override;

  void UploadFinished(bool ok);

 private:
  // Provides us with the interval between successful uploads.
  base::RepeatingCallback<base::TimeDelta(void)> get_interval_callback_;

  // Initial time to wait between upload retry attempts.
  const base::TimeDelta initial_backoff_interval_;

  // Time to wait for the next upload attempt if the next one fails.
  base::TimeDelta backoff_interval_;

  bool randomize_upload_interval_;

  base::TimeDelta average_upload_interval_;
};

}  // namespace brave

#endif  // BRAVE_COMPONENTS_P3A_BRAVE_P3A_SCHEDULER_H_
