/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_rewards/browser/brave_rewards_service.h"

#include <utility>

#include "brave/components/brave_rewards/browser/rewards_service.h"

namespace brave_rewards {

BraveRewardsService::BraveRewardsService(RewardsService* rewards_service)
    : rewards_service_(rewards_service) {
  DCHECK(rewards_service_);
}

BraveRewardsService::~BraveRewardsService() = default;

mojo::PendingRemote<mojom::BraveRewardsService>
BraveRewardsService::MakeRemote() {
  mojo::PendingRemote<mojom::BraveRewardsService> remote;
  receivers_.Add(this, remote.InitWithNewPipeAndPassReceiver());
  return remote;
}

void BraveRewardsService::Bind(
    mojo::PendingReceiver<mojom::BraveRewardsService> receiver) {
  receivers_.Add(this, std::move(receiver));
}

void BraveRewardsService::GetUserType(GetUserTypeCallback callback) {
  rewards_service_->GetUserType(std::move(callback));
}

}  // namespace brave_rewards
