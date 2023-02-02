// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import styled from 'styled-components'
import { WalletButton } from '../../../../shared/style'
import MoreCircles from '../../../../../assets/svg-icons/more-circles.svg'

export const FilterTokenRow = styled.div`
  display: flex;
  align-items: center;
  justify-content: space-between;
  flex-direction: row;
  width: 100%;
  gap: 14px;
  position: relative;
`

export const NftGrid = styled.div`
  display: grid;
  grid-template-columns: repeat(5, 1fr);
  grid-gap: 25px;
  box-sizing: border-box;
  width: 100%;
  padding-top: 10px;
  @media screen and (max-width: 1350px) {
    grid-template-columns: repeat(4, 1fr);
  }
  @media screen and (max-width: 1150px) {
    grid-template-columns: repeat(3, 1fr);
  }
  @media screen and (max-width: 950px) {
    grid-template-columns: repeat(2, 1fr);
  }
`

export const EmptyStateText = styled.div`
  text-align: center;
  padding: 30px 0;
  color: ${p => p.theme.color.text03};
  font-size: 14px;
  font-family: Poppins;
`

export const MoreButton = styled(WalletButton)`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  padding: 10px;
  width: 38px;
  height:38px;
  border: 1px solid ${p => p.theme.color.interactive08};
  background-color: ${(p) => p.theme.color.background02};
  border-radius: 6px;
  align-self: flex-start;
  cursor: pointer;
`

export const MoreIcon = styled.div`
  width: 20px;
  height: 20px;
  background-color: ${(p) => p.theme.color.interactive07};
  mask-image: url(${MoreCircles});
  background-color: #656565;
  mask-size: contain;
  mask-repeat: no-repeat;
  mask-position: center;
`
