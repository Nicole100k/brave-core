/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_BRAVE_REWARDS_BRAVE_REWARDS_SERVICE_FACTORY_H_
#define BRAVE_BROWSER_BRAVE_REWARDS_BRAVE_REWARDS_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "brave/components/brave_rewards/common/brave_rewards.mojom.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "content/public/browser/browser_context.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"

namespace brave_rewards {

class BraveRewardsService;

class BraveRewardsServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  static mojo::PendingRemote<mojom::BraveRewardsService> GetForContext(
      content::BrowserContext* context);

  static BraveRewardsService* GetServiceForContext(
      content::BrowserContext* context);

  static BraveRewardsServiceFactory* GetInstance();

  static void BindForContext(
      content::BrowserContext* context,
      mojo::PendingReceiver<mojom::BraveRewardsService> receiver);

 private:
  friend struct base::DefaultSingletonTraits<BraveRewardsServiceFactory>;

  BraveRewardsServiceFactory();
  ~BraveRewardsServiceFactory() override;

  BraveRewardsServiceFactory(const BraveRewardsServiceFactory&) = delete;
  BraveRewardsServiceFactory& operator=(const BraveRewardsServiceFactory&) =
      delete;

  // BrowserContextKeyedServiceFactory:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const override;
};

}  // namespace brave_rewards

#endif  // BRAVE_BROWSER_BRAVE_REWARDS_BRAVE_REWARDS_SERVICE_FACTORY_H_
