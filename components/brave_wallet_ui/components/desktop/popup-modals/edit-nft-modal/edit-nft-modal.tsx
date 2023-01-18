// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'

import { BraveWallet } from '../../../../constants/types'
import { PopupModal } from '../..'
import { AddNftForm } from '../../../shared/add-custom-token-form/add-nft-form'
import { StyledWrapper, EditWrapper } from './edit-nft-modal.style'

interface Props {
  nftToken: BraveWallet.BlockchainToken
  onClose: () => void
  onHideForm: () => void
  onTokenFound: (contractAddress: string) => void
  onChangeContractAddress: (contractAddress: string) => void
}

export const EditNftModal = ({ nftToken, onClose, onHideForm, onTokenFound, onChangeContractAddress }: Props) => {
  return (
    <StyledWrapper>
      <PopupModal
        title='Edit NFT'
        onClose={onClose}
        width='584px'
        showDivider={true}
      >
          <EditWrapper>
            <AddNftForm
              selectedAsset={nftToken}
              contractAddress={nftToken.contractAddress}
              onHideForm={onHideForm}
              onTokenFound={onTokenFound}
              onChangeContractAddress={onChangeContractAddress}
              />
          </EditWrapper>
        </PopupModal>
    </StyledWrapper>
  )
}
