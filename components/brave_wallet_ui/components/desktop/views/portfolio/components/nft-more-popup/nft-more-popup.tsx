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
  EditIcon,
  EyeOffIcon
} from './nft-more-popup.styles'

interface Props {
  onEditNft: () => void
  onHideNft: () => void
}

export const NftMorePopup = (props: Props) => {
  const {
    onEditNft,
    onHideNft
  } = props

  return (
    <StyledWrapper>
      <PopupButton onClick={onEditNft}>
        <EditIcon />
        <PopupButtonText>Edit</PopupButtonText>
      </PopupButton>
      <PopupButton onClick={onHideNft}>
        <EyeOffIcon />
        <PopupButtonText>Hide</PopupButtonText>
      </PopupButton>
    </StyledWrapper>
  )
}
