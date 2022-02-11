import * as React from 'react'
import {
  UserAccountType,
  OrderTypes,
  BuySendSwapViewTypes,
  SlippagePresetObjectType,
  ExpirationPresetObjectType,
  ToOrFromType,
  BraveWallet,
  SwapValidationErrorType
} from '../../../constants/types'
import {
  AccountsAssetsNetworks,
  Header,
  Swap
} from '..'

export interface Props {
  accounts: UserAccountType[]
  networkList: BraveWallet.EthereumChain[]
  orderType: OrderTypes
  swapToAsset: BraveWallet.BlockchainToken
  swapFromAsset: BraveWallet.BlockchainToken
  selectedNetwork: BraveWallet.EthereumChain
  selectedAccount: UserAccountType
  exchangeRate: string
  slippageTolerance: SlippagePresetObjectType
  orderExpiration: ExpirationPresetObjectType
  fromAmount: string
  toAmount: string
  fromAssetBalance: string
  toAssetBalance: string
  swapFromAssetOptions: BraveWallet.BlockchainToken[]
  swapToAssetOptions: BraveWallet.BlockchainToken[]
  isFetchingQuote: boolean
  isSubmitDisabled: boolean
  validationError?: SwapValidationErrorType
  customSlippageTolerance: string
  toOrFrom: ToOrFromType
  onCustomSlippageToleranceChange: (value: string) => void
  onSubmitSwap: () => void
  flipSwapAssets: () => void
  onSelectNetwork: (network: BraveWallet.EthereumChain) => void
  onSelectAccount: (account: UserAccountType) => void
  onToggleOrderType: () => void
  onSelectSwapAsset: (asset: BraveWallet.BlockchainToken, toOrFrom: ToOrFromType) => void
  onSelectSlippageTolerance: (slippage: SlippagePresetObjectType) => void
  onSelectExpiration: (expiration: ExpirationPresetObjectType) => void
  onSetExchangeRate: (value: string) => void
  onSetFromAmount: (value: string) => void
  onSetToAmount: (value: string) => void
  onSelectPresetAmount: (percent: number) => void
  onQuoteRefresh: () => void
  onAddNetwork: () => void
  onAddAsset: () => void
  onFilterAssetList: (asset: BraveWallet.BlockchainToken, toOrFrom: ToOrFromType) => void
}

function SwapTab (props: Props) {
  const {
    accounts,
    networkList,
    orderType,
    swapToAsset,
    swapFromAsset,
    selectedNetwork,
    selectedAccount,
    exchangeRate,
    slippageTolerance,
    orderExpiration,
    fromAmount,
    toAmount,
    fromAssetBalance,
    toAssetBalance,
    swapFromAssetOptions,
    swapToAssetOptions,
    isFetchingQuote,
    isSubmitDisabled,
    validationError,
    customSlippageTolerance,
    toOrFrom,
    onCustomSlippageToleranceChange,
    onSubmitSwap,
    flipSwapAssets,
    onSelectNetwork,
    onSelectAccount,
    onToggleOrderType,
    onSelectSwapAsset,
    onSelectSlippageTolerance,
    onSelectExpiration,
    onSetExchangeRate,
    onSetFromAmount,
    onSetToAmount,
    onSelectPresetAmount,
    onQuoteRefresh,
    onAddNetwork,
    onAddAsset,
    onFilterAssetList
  } = props
  const [swapView, setSwapView] = React.useState<BuySendSwapViewTypes>('swap')

  const onChangeSwapView = (view: BuySendSwapViewTypes) => {
    setSwapView(view)
  }

  const onClickSelectNetwork = (network: BraveWallet.EthereumChain) => () => {
    onSelectNetwork(network)
    setSwapView('swap')
  }

  const onClickSelectAccount = (account: UserAccountType) => () => {
    onSelectAccount(account)
    setSwapView('swap')
  }

  const onSelectAsset = (asset: BraveWallet.BlockchainToken) => () => {
    onSelectSwapAsset(asset, toOrFrom)
    setSwapView('swap')
  }

  const onInputChange = (value: string, name: string) => {
    if (name === 'to') {
      onSetToAmount(value)
    }
    if (name === 'from') {
      onSetFromAmount(value)
    }
    if (name === 'rate') {
      onSetExchangeRate(value)
    }
  }

  const goBack = () => {
    setSwapView('swap')
  }

  return (
    <>
      {swapView === 'swap' &&
        <>
          <Header
            selectedAccount={selectedAccount}
            selectedNetwork={selectedNetwork}
            onChangeSwapView={onChangeSwapView}
          />
          <Swap
            toAsset={swapToAsset}
            fromAsset={swapFromAsset}
            toAmount={toAmount}
            fromAmount={fromAmount}
            orderType={orderType}
            exchangeRate={exchangeRate}
            slippageTolerance={slippageTolerance}
            orderExpiration={orderExpiration}
            isFetchingQuote={isFetchingQuote}
            isSubmitDisabled={isSubmitDisabled}
            validationError={validationError}
            customSlippageTolerance={customSlippageTolerance}
            onCustomSlippageToleranceChange={onCustomSlippageToleranceChange}
            onInputChange={onInputChange}
            onFlipAssets={flipSwapAssets}
            onSubmitSwap={onSubmitSwap}
            onSelectPresetAmount={onSelectPresetAmount}
            onSelectSlippageTolerance={onSelectSlippageTolerance}
            onSelectExpiration={onSelectExpiration}
            onChangeSwapView={onChangeSwapView}
            onToggleOrderType={onToggleOrderType}
            onFilterAssetList={onFilterAssetList}
            fromAssetBalance={fromAssetBalance}
            toAssetBalance={toAssetBalance}
            onQuoteRefresh={onQuoteRefresh}
          />
        </>
      }
      {swapView !== 'send' &&
        <AccountsAssetsNetworks
          selectedAccount={selectedAccount}
          selectedNetwork={selectedNetwork}
          accounts={accounts}
          networkList={networkList}
          goBack={goBack}
          assetOptions={toOrFrom === 'from' ? swapFromAssetOptions : swapToAssetOptions}
          onClickSelectAccount={onClickSelectAccount}
          onClickSelectNetwork={onClickSelectNetwork}
          onSelectedAsset={onSelectAsset}
          selectedView={swapView}
          onAddNetwork={onAddNetwork}
          onAddAsset={onAddAsset}
        />
      }
    </>
  )
}

export default SwapTab
