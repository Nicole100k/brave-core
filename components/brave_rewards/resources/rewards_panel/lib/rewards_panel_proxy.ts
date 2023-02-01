/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { BraveRewardsServiceRemote } from 'gen/brave/components/brave_rewards/common/brave_rewards.mojom.m.js'
import { PanelCallbackRouter, PanelHandlerRemote, PanelHandlerFactory } from 'gen/brave/components/brave_rewards/common/brave_rewards_panel.mojom.m.js'

let instance: RewardsPanelProxy|null = null

export class RewardsPanelProxy {
  callbackRouter: PanelCallbackRouter
  handler: PanelHandlerRemote
  rewardsService: BraveRewardsServiceRemote

  constructor (
      callbackRouter: PanelCallbackRouter,
      handler: PanelHandlerRemote,
      rewardsService: BraveRewardsServiceRemote) {
    this.callbackRouter = callbackRouter
    this.handler = handler
    this.rewardsService = rewardsService
  }

  static getInstance (): RewardsPanelProxy {
    if (!instance) {
      const callbackRouter = new PanelCallbackRouter()
      const handler = new PanelHandlerRemote()
      const rewardsService = new BraveRewardsServiceRemote()
      PanelHandlerFactory.getRemote().createPanelHandler(
        callbackRouter.$.bindNewPipeAndPassRemote(),
        handler.$.bindNewPipeAndPassReceiver(),
        rewardsService.$.bindNewPipeAndPassReceiver())
      instance = new RewardsPanelProxy(callbackRouter, handler, rewardsService)
    }
    return instance
  }
}
