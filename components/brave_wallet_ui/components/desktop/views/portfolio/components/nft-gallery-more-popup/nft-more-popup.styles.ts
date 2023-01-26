// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'
import PlusSvgIcon from '../../../../../../assets/svg-icons/plus-icon.svg'
import { WalletButton } from '../../../../../shared/style'

export const StyledWrapper = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: 7px;
  background-color: ${(p) => p.theme.color.background02};
  border-radius: 8px;
  box-shadow: 0px 4px 13px -2px rgba(0, 0, 0, 0.1);
  border: 1px solid ${p => p.theme.color.divider01};
  position: absolute;
  top: 39px;
  right: 0;
  z-index: 3;
  width: 197px;
`

export const PopupButton = styled(WalletButton)`
  display: flex;
  align-items: center;
  justify-content: flex-start;
  text-align: left;
  cursor: pointer;
  width: 100%;
  border-radius: 8px;
  outline: none;
  border: none;
  background: none;
  padding: 10px 0px;
  margin: 0px;
  background-color: transparent;
`

export const PopupButtonText = styled.span`
  flex: 1;
  font-family: Poppins;
  font-size: 14px;
  font-weight: 400;
  letter-spacing: 0.01em;
  line-height: 24px;
  color: #1D1F25;
`
const PopupButtonIcon = styled.div`
  width: 12px;
  height: 12px;
  margin-right: 16px;
  margin-left: 16px;
  mask-size: contain;
  background-color: ${(p) => p.theme.color.interactive07};
`

export const PlusIcon = styled(PopupButtonIcon)`
  mask-image: url(${PlusSvgIcon});
  background-color: #6B7084;
`
