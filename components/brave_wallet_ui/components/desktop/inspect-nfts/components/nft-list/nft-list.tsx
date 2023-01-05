// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'

// utils
import { useUnsafeWalletSelector } from '../../../../../common/hooks/use-safe-selector'
import { WalletSelectors } from '../../../../../common/selectors'
import { getTokensNetwork } from '../../../../../utils/network-utils'
import { useNftPin } from '../../../../../common/hooks/nft-pin'

// components
import { NftIconWithNetworkIcon } from '../../../../shared/nft-icon/nft-icon-with-network-icon'
import { NftCountHeading } from '../../inspects-nfts.styles'

// styles
import { NftListWrapper, List, NftItem, NftItemOverlay, PiningMessage } from './nft-list.styles'

export const NftList = () => {
  const networkList = useUnsafeWalletSelector(WalletSelectors.networkList)

  // hooks
  const { pinnableNftsCount, nonFungibleTokens } = useNftPin()

  return (
    <NftListWrapper>
      <NftCountHeading>{pinnableNftsCount} out of {nonFungibleTokens.length} are available!</NftCountHeading>
      <List>
        {nonFungibleTokens.map(({ canBePinned, token }) => (
          <NftItem key={`nft-item-${token.contractAddress}-${token.tokenId}`}>
            {!canBePinned &&
              <NftItemOverlay>
                <PiningMessage>Unable to pin</PiningMessage>
              </NftItemOverlay>
            }
            <NftIconWithNetworkIcon
              key={`${token.contractAddress}-${token.tokenId}`}
              tokensNetwork={getTokensNetwork(networkList, token)}
              icon={token.logo}
              circular={true}
              responsive={true}
              disabled={canBePinned}
            />
          </NftItem>
        ))}
      </List>
    </NftListWrapper>
  )
}
