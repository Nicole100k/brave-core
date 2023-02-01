/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_rewards/brave_rewards_service_factory.h"

#include <utility>

#include "brave/browser/brave_rewards/rewards_service_factory.h"
#include "brave/browser/brave_rewards/rewards_util.h"
#include "brave/components/brave_rewards/browser/brave_rewards_service.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"

namespace brave_rewards {

namespace {

bool IsAllowedForContext(content::BrowserContext* context) {
  Profile* profile = Profile::FromBrowserContext(context);
  return profile && IsSupportedForProfile(profile);
}

}  // namespace

// static
BraveRewardsServiceFactory* BraveRewardsServiceFactory::GetInstance() {
  return base::Singleton<BraveRewardsServiceFactory>::get();
}

// static
mojo::PendingRemote<mojom::BraveRewardsService>
BraveRewardsServiceFactory::GetForContext(content::BrowserContext* context) {
  if (!IsAllowedForContext(context)) {
    return mojo::PendingRemote<mojom::BraveRewardsService>();
  }

  auto* service = static_cast<BraveRewardsService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));

  DCHECK(service);
  return service->MakeRemote();
}

// static
BraveRewardsService* BraveRewardsServiceFactory::GetServiceForContext(
    content::BrowserContext* context) {
  if (!IsAllowedForContext(context)) {
    return nullptr;
  }
  return static_cast<BraveRewardsService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
void BraveRewardsServiceFactory::BindForContext(
    content::BrowserContext* context,
    mojo::PendingReceiver<mojom::BraveRewardsService> receiver) {
  auto* service = BraveRewardsServiceFactory::GetServiceForContext(context);
  if (service) {
    service->Bind(std::move(receiver));
  }
}

BraveRewardsServiceFactory::BraveRewardsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "BraveRewardsService",
          BrowserContextDependencyManager::GetInstance()) {
  DependsOn(RewardsServiceFactory::GetInstance());
}

BraveRewardsServiceFactory::~BraveRewardsServiceFactory() = default;

KeyedService* BraveRewardsServiceFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  auto* profile = Profile::FromBrowserContext(context);
  DCHECK(profile);
  return new BraveRewardsService(RewardsServiceFactory::GetForProfile(profile));
}

}  // namespace brave_rewards
