// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import * as React from 'react'
import { useSelector } from 'react-redux'

// types
import { WalletState } from '../../../constants/types'

// Utils
import Amount from '../../../utils/amount'
import { getLocale } from '../../../../common/locale'

// Hooks
import { usePendingTransactions } from '../../../common/hooks/use-pending-transaction'

// Components
import Tooltip from '../../shared/tooltip/index'
import CreateSiteOrigin from '../../shared/create-site-origin/index'
import PanelTab from '../panel-tab'
import { TransactionInfo } from './transaction-info'
import { SolanaTransactionDetailBox } from '../transaction-box/solana-transaction-detail-box'

// Styles
import { Skeleton } from '../../shared/loading-skeleton/styles'
import {
  TabRow,
  URLText,
  WarningBox,
  WarningTitle,
  LearnMoreButton,
  WarningBoxTitleRow
} from '../shared-panel-styles'
import {
  StyledWrapper,
  FromCircle,
  ToCircle,
  AccountNameText,
  TransactionAmountBig,
  TransactionFiatAmountBig,
  MessageBox,
  TransactionTypeText,
  AccountCircleWrapper,
  ArrowIcon,
  FromToRow,
  TopRow, NetworkText
} from './style'
import { TransactionQueueStep } from './common/queue'
import { Footer } from './common/footer'
import { reduceNetworkDisplayName } from '../../../utils/network-utils'

type confirmPanelTabs = 'transaction' | 'details'
interface Props {
  onConfirm: () => void
  onReject: () => void
}

const onClickLearnMore = () => {
  chrome.tabs.create({ url: 'https://support.brave.com/hc/en-us/articles/5546517853325' }, () => {
    if (chrome.runtime.lastError) {
      console.error('tabs.create failed: ' + chrome.runtime.lastError.message)
    }
  })
}

export const ConfirmSolanaTransactionPanel = ({
  onConfirm,
  onReject
}: Props) => {
  // redux
  const {
    activeOrigin,
    defaultCurrencies,
    selectedPendingTransaction: transactionInfo
  } = useSelector(({ wallet }: { wallet: WalletState }) => wallet)

  const originInfo = transactionInfo?.originInfo ?? activeOrigin

  // custom hooks
  const pendingTxInfo = usePendingTransactions()
  const {
    fromAddress,
    fromOrb,
    isAssociatedTokenAccountCreation,
    toOrb,
    transactionDetails,
    transactionTitle,
    isSolanaDappTransaction,
    fromAccountName,
    transactionsNetwork
  } = pendingTxInfo

  // state
  const [selectedTab, setSelectedTab] = React.useState<confirmPanelTabs>('transaction')

  // methods
  const onSelectTab = React.useCallback(
    (tab: confirmPanelTabs) => () => setSelectedTab(tab),
  [])

  // render
  if (!transactionDetails || !transactionInfo) {
    return <StyledWrapper>
      <Skeleton width={'100%'} height={'100%'} enableAnimation />
    </StyledWrapper>
  }

  return (
    <StyledWrapper>
      <TopRow>
        <NetworkText>{reduceNetworkDisplayName(transactionsNetwork.chainName)}</NetworkText>
        <TransactionQueueStep />
      </TopRow>

      <AccountCircleWrapper>
        <FromCircle orb={fromOrb} />
        <ToCircle orb={toOrb} />
      </AccountCircleWrapper>
      <URLText>
        <CreateSiteOrigin
          originSpec={originInfo.originSpec}
          eTldPlusOne={originInfo.eTldPlusOne}
        />
      </URLText>
      <FromToRow>
        <Tooltip
          text={fromAddress}
          isAddress={true}
          position='left'
        >
          <AccountNameText>{fromAccountName}</AccountNameText>
        </Tooltip>

        {transactionDetails.recipient && transactionDetails.recipient !== fromAddress &&
          <>
            <ArrowIcon />
            <Tooltip
              text={transactionDetails.recipient}
              isAddress={true}
              position='right'
            >
              <AccountNameText>{transactionDetails.recipientLabel}</AccountNameText>
            </Tooltip>
          </>
        }
      </FromToRow>

      <TransactionTypeText>{transactionTitle}</TransactionTypeText>

      {!isSolanaDappTransaction &&
        <>
          <TransactionAmountBig>
            {new Amount(transactionDetails.valueExact)
                .formatAsAsset(undefined, transactionDetails.symbol)
            }
          </TransactionAmountBig>

          <TransactionFiatAmountBig>
            {
              transactionDetails.fiatValue.formatAsFiat(defaultCurrencies.fiat)
            }
          </TransactionFiatAmountBig>
        </>
      }

      {isAssociatedTokenAccountCreation &&
        <WarningBox warningType='warning'>
          <WarningBoxTitleRow>
            <WarningTitle warningType='warning'>
              {getLocale('braveWalletConfirmTransactionAccountCreationFee')}
              <LearnMoreButton
                onClick={onClickLearnMore}
              >
                {getLocale('braveWalletAllowAddNetworkLearnMoreButton')}
              </LearnMoreButton>
            </WarningTitle>
          </WarningBoxTitleRow>
        </WarningBox>
      }

      <TabRow>
        <PanelTab
          isSelected={selectedTab === 'transaction'}
          onSubmit={onSelectTab('transaction')}
          text='Transaction'
        />
        <PanelTab
          isSelected={selectedTab === 'details'}
          onSubmit={onSelectTab('details')}
          text='Details'
        />
      </TabRow>

      <MessageBox
        isDetails={selectedTab === 'details'}
        isApprove={false}
      >

        {selectedTab === 'transaction'
          ? <TransactionInfo />
          : <SolanaTransactionDetailBox
              data={transactionInfo?.txDataUnion?.solanaTxData}
              instructions={transactionDetails.instructions}
              txType={transactionInfo.txType}
            />
        }
      </MessageBox>
      <Footer onConfirm={onConfirm} onReject={onReject} />
    </StyledWrapper>
  )
}

export default ConfirmSolanaTransactionPanel
