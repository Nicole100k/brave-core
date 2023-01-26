// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

// Styled Components
import {
  StyledWrapper,
  PopupButton,
  PopupButtonText,
  PlusIcon
} from './nft-more-popup.styles'

interface Props {
  onImportNft: () => void
}

export const NftGalleryMorePopup = (props: Props) => {
  const {
    onImportNft
  } = props

  return (
    <StyledWrapper>
      <PopupButton onClick={onImportNft}>
        <PlusIcon />
        <PopupButtonText>Import NFT</PopupButtonText>
      </PopupButton>
    </StyledWrapper>
  )
}
