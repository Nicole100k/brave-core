// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { useSelector } from 'react-redux'
import { WalletState } from '../../../constants/types'
import Amount from '../../../utils/amount'
import { getLocale } from '../../../../common/locale'
import { usePendingTransactions } from '../../../common/hooks/use-pending-transaction'
import {
  TransactionTitle,
  TransactionTypeText,
  TransactionText, Divider,
  SectionRow,
  EditButton
} from './style'

interface Erc20TransactionInfoProps {
  onToggleEditGas: () => void
}

export const Erc20ApproveTransactionInfo = ({ onToggleEditGas }: Erc20TransactionInfoProps) => {
  const {
    currentTokenAllowance, transactionDetails, transactionsNetwork
  } = usePendingTransactions()

  // redux
  const {
    defaultCurrencies
  } = useSelector((state: { wallet: WalletState }) => state.wallet)

  // exit early if no details
  if (!transactionDetails) {
    return null
  }

  // render
  return <>
    <SectionRow>
      <TransactionTitle>{getLocale('braveWalletAllowSpendTransactionFee')}</TransactionTitle>
      <EditButton onClick={onToggleEditGas}>{getLocale('braveWalletAllowSpendEditButton')}</EditButton>
    </SectionRow>

    <TransactionTypeText>
      {transactionsNetwork && new Amount(transactionDetails.gasFee)
        .divideByDecimals(transactionsNetwork.decimals)
        .formatAsAsset(6, transactionsNetwork.symbol)}
    </TransactionTypeText>

    <TransactionText hasError={false}>
      {new Amount(transactionDetails.gasFeeFiat)
        .formatAsFiat(defaultCurrencies.fiat)}
    </TransactionText>

    {transactionDetails.insufficientFundsForGasError &&
      <TransactionText hasError={true}>
        {getLocale('braveWalletSwapInsufficientFundsForGas')}
      </TransactionText>
    }

    {transactionDetails.insufficientFundsForGasError === false &&
      transactionDetails.insufficientFundsError &&
      <TransactionText hasError={true}>
        {getLocale('braveWalletSwapInsufficientBalance')}
      </TransactionText>
    }

    <Divider />

    <TransactionTitle>{getLocale('braveWalletAllowSpendCurrentAllowance')}</TransactionTitle>
    <TransactionTypeText>{currentTokenAllowance} {transactionDetails.symbol}</TransactionTypeText>

    <Divider />

    <TransactionTitle>{getLocale('braveWalletAllowSpendProposedAllowance')}</TransactionTitle>
    <TransactionTypeText>
      {transactionDetails.isApprovalUnlimited
        ? getLocale('braveWalletTransactionApproveUnlimited')
        : new Amount(transactionDetails.valueExact)
          .formatAsAsset(undefined, transactionDetails.symbol)}
    </TransactionTypeText>

  </>
}
