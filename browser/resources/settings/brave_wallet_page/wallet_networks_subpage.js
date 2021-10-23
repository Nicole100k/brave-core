/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import 'chrome://resources/cr_elements/cr_button/cr_button.m.js';
import {BraveWalletBrowserProxyImpl} from './brave_wallet_browser_proxy.m.js';
import {I18nBehavior} from 'chrome://resources/js/i18n_behavior.m.js';
import {Polymer, html} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import {PrefsBehavior} from '../prefs/prefs_behavior.js';
import './add_wallet_network_dialog.js';

/**
* @fileoverview
* 'settings-sync-subpage' is the settings page content
*/
Polymer({
  is: 'settings-wallet-networks-subpage',

  _template: html`{__html_template__}`,
  
  behaviors: [
    PrefsBehavior,
    I18nBehavior
  ],

  properties: {
    networks: {
      type: Array,
      value() {
        return [];
      },
    },
    showAddWalletNetworkDialog_: {
      type: Boolean,
      value: false,
    },
    selectedNetwork: {
      type: Object,
      value: {}
    }
  },

  browserProxy_: null,
  /** @override */
  created: function() {
    this.browserProxy_ = BraveWalletBrowserProxyImpl.getInstance();
  },

  notifyKeylist: function() {
    const keysList =
    /** @type {IronListElement} */ (this.$$('#networksList'));
    if (keysList) {
      keysList.notifyResize();
    }
  },

  /*++++++
  * @override */
  ready: function() {
    this.updateNetworks();
  },

  isDefaultNetwork: function (chainId) {
    return (chainId ===
        this.getPref('brave.wallet.wallet_current_chain_id').value)
  },
  hideNativeCurrencyInfo: function(item) {
    return !item.nativeCurrency || item.nativeCurrency.name.trim() === ''
  },
  getItemDescritionText: function(item) {
    const url = (item.rpcUrls && item.rpcUrls.length) ?  item.rpcUrls[0] : '';
    return item.chainId + ' ' + url
  },

  onDeleteActionTapped_: function(event) {
    var message = this.i18n('walletDeleteNetworkConfirmation',
                            event.model.item.chainName)
    if (!window.confirm(message))
      return

    this.browserProxy_.removeEthereumChain(event.model.item.chainId).
        then(success => { this.updateNetworks() })
  },

  onAddNetworkTap_: function(item) {
    this.showAddWalletNetworkDialog_ = true
  },
  onItemDoubleClick: function(event) {
    this.selectedNetwork = event.model.item
    this.showAddWalletNetworkDialog_ = true
  },
  updateNetworks: function() {
    this.browserProxy_.getCustomNetworksList().then(payload => {
      if (!payload)
        return;
      this.networks = JSON.parse(payload);
      this.notifyKeylist();
    });
  },

  onAddNetworkDialogClosed_: function() {
    this.showAddWalletNetworkDialog_ = false
    this.selectedNetwork = {}
    this.updateNetworks();
  }
});

