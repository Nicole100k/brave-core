/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_BRAVE_REWARDS_SERVICE_H_
#define BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_BRAVE_REWARDS_SERVICE_H_

#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "brave/components/brave_rewards/common/brave_rewards.mojom.h"
#include "components/keyed_service/core/keyed_service.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver_set.h"

namespace brave_rewards {

class RewardsService;

class BraveRewardsService : public KeyedService,
                            public mojom::BraveRewardsService {
 public:
  explicit BraveRewardsService(RewardsService* rewards_service);
  ~BraveRewardsService() override;

  BraveRewardsService(const BraveRewardsService&) = delete;
  BraveRewardsService& operator=(const BraveRewardsService&) = delete;

  mojo::PendingRemote<mojom::BraveRewardsService> MakeRemote();
  void Bind(mojo::PendingReceiver<mojom::BraveRewardsService> receiver);

  // mojom::BraveRewardsService:
  void GetUserType(GetUserTypeCallback callback) override;

 private:
  raw_ptr<RewardsService> rewards_service_ = nullptr;
  mojo::ReceiverSet<mojom::BraveRewardsService> receivers_;
  base::WeakPtrFactory<BraveRewardsService> weak_factory_{this};
};

}  // namespace brave_rewards

#endif  // BRAVE_COMPONENTS_BRAVE_REWARDS_BROWSER_BRAVE_REWARDS_SERVICE_H_
