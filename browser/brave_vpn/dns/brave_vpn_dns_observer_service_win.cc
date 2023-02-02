/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_vpn/dns/brave_vpn_dns_observer_service_win.h"

#include <vector>

#include "base/strings/string_util.h"
#include "brave/browser/ui/views/brave_vpn/brave_vpn_dns_settings_notificiation_dialog_view.h"
#include "brave/components/brave_vpn/browser/connection/win/brave_vpn_helper/brave_vpn_helper_constants.h"
#include "brave/components/brave_vpn/browser/connection/win/brave_vpn_helper/brave_vpn_helper_state.h"
#include "brave/components/brave_vpn/common/brave_vpn_utils.h"
#include "brave/components/brave_vpn/common/pref_names.h"
#include "chrome/browser/net/secure_dns_config.h"
#include "chrome/browser/net/stub_resolver_config_reader.h"
#include "chrome/browser/net/system_network_context_manager.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/browser_finder.h"
#include "chrome/browser/ui/browser_window.h"
#include "chrome/browser/ui/simple_message_box.h"
#include "chrome/common/pref_names.h"
#include "chrome/grit/chromium_strings.h"
#include "components/grit/brave_components_strings.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "ui/base/l10n/l10n_util.h"

namespace brave_vpn {

namespace {
const char kCloudflareDnsProviderURL[] =
    "https://chrome.cloudflare-dns.com/dns-query";

// Helper service has 3 fail actions configured to autorestart the service if
// crashed. The check happens before the service started and counter set to 1,
// thus we calculate attempts from 0 -> 2.
const int kHelperServiceFailActionsNumber = 2;

void SkipDNSDialog(PrefService* prefs, bool checked) {
  if (!prefs)
    return;
  prefs->SetBoolean(prefs::kBraveVpnShowDNSPolicyWarningDialog, !checked);
}

gfx::NativeWindow GetAnchorBrowserWindow() {
  auto* browser = chrome::FindLastActive();
  return browser ? browser->window()->GetNativeWindow()
                 : gfx::kNullNativeWindow;
}

bool AreConfigsEqual(SecureDnsConfig& one, SecureDnsConfig& two) {
  return one.mode() == two.mode() &&
         one.management_mode() == two.management_mode() &&
         one.doh_servers() == two.doh_servers();
}

}  // namespace

BraveVpnDnsObserverService::BraveVpnDnsObserverService(
    PrefService* local_state,
    PrefService* profile_prefs)
    : local_state_(local_state), profile_prefs_(profile_prefs) {
  DCHECK(profile_prefs_);
  DCHECK(local_state_);
  local_state_->ClearPref(::prefs::kBraveVpnDnsConfig);
}

BraveVpnDnsObserverService::~BraveVpnDnsObserverService() = default;

void BraveVpnDnsObserverService::ShowPolicyWarningMessage() {
  if (!profile_prefs_->GetBoolean(prefs::kBraveVpnShowDNSPolicyWarningDialog)) {
    return;
  }

  if (policy_callback_) {
    std::move(policy_callback_).Run();
    return;
  }

  chrome::ShowWarningMessageBoxWithCheckbox(
      GetAnchorBrowserWindow(), l10n_util::GetStringUTF16(IDS_PRODUCT_NAME),
      l10n_util::GetStringUTF16(IDS_BRAVE_VPN_DNS_POLICY_ALERT),
      l10n_util::GetStringUTF16(IDS_BRAVE_VPN_DNS_POLICY_CHECKBOX),
      base::BindOnce(&SkipDNSDialog, profile_prefs_));
}

void BraveVpnDnsObserverService::ShowVpnDnsSettingsNotificationDialog() {
  if (dialog_callback_) {
    dialog_callback_.Run();
    return;
  }
  BraveVpnDnsSettingsNotificiationDialogView::Show(chrome::FindLastActive());
}

void BraveVpnDnsObserverService::UnlockDNS() {
  local_state_->ClearPref(::prefs::kBraveVpnDnsConfig);
  // Read DNS config to initiate update of actual state.
  SystemNetworkContextManager::GetStubResolverConfigReader()
      ->UpdateNetworkService(false);
}

absl::optional<base::win::RegKey*>
BraveVpnDnsObserverService::GetServiceStorageKey() {
  if (!service_storage_key_.Valid()) {
    service_storage_key_.Open(HKEY_LOCAL_MACHINE,
                              brave_vpn::kBraveVpnHelperRegistryStoragePath,
                              KEY_READ);
    if (!service_storage_key_.Valid()) {
      LOG(ERROR) << "Failed to read the successful launch counter";
      return absl::nullopt;
    }
    // Watch for service failure actions counter to lock DNS if needed.
    service_storage_key_.StartWatching(
        base::BindOnce(&BraveVpnDnsObserverService::OnRegistryKeyChanged,
                       weak_ptr_factory_.GetWeakPtr()));
  }
  return &service_storage_key_;
}

bool BraveVpnDnsObserverService::IsDNSHelperLive() {
  if (dns_helper_live_for_testing_.has_value()) {
    return dns_helper_live_for_testing_.value();
  }
  // If BraveVpnHelper is live we should not override DNS because it will be
  // handled by the service.
  if (!brave_vpn::IsBraveVPNHelperServiceInstalled()) {
    return false;
  }
  auto service_storage_key = GetServiceStorageKey();
  if (!service_storage_key.has_value()) {
    return false;
  }
  auto* storage_key = service_storage_key.value();
  DWORD launch = 0;
  storage_key->ReadValueDW(brave_vpn::kBraveVpnHelperLaunchCounterValue,
                           &launch);
  if (launch > kHelperServiceFailActionsNumber) {
    return false;
  }
  // if service is not started yet set timer to re-check after some time
  if (launch == 0) {
    // Set delayed check if service will not start by some reasons.
    content::GetUIThreadTaskRunner({})->PostDelayedTask(
        FROM_HERE,
        base::BindOnce(&BraveVpnDnsObserverService::OnCheckIfServiceStarted,
                       weak_ptr_factory_.GetWeakPtr(), launch),
        base::Seconds(10));
  }
  return true;
}

void BraveVpnDnsObserverService::OnCheckIfServiceStarted(DWORD previous_value) {
  auto service_storage_key = GetServiceStorageKey();
  if (!service_storage_key.has_value()) {
    return;
  }
  auto* storage_key = service_storage_key.value();
  DWORD current = -1;
  storage_key->ReadValueDW(brave_vpn::kBraveVpnHelperLaunchCounterValue,
                           &current);
  if (current == previous_value) {
    LockDNS();
  }
}

void BraveVpnDnsObserverService::OnRegistryKeyChanged() {
  if (vpn_state_ == brave_vpn::mojom::ConnectionState::DISCONNECTED) {
    return;
  }
  auto service_storage_key = GetServiceStorageKey();
  if (!service_storage_key.has_value()) {
    return;
  }
  auto* storage_key = service_storage_key.value();
  DWORD launch = 0;
  storage_key->ReadValueDW(brave_vpn::kBraveVpnHelperLaunchCounterValue,
                           &launch);
  // The service exceed failure actions crash value and will not be restarted.
  // Lock DNS with DoH.
  if (launch > kHelperServiceFailActionsNumber) {
    return LockDNS();
  }

  // |OnRegistryKeyChanged| is removed as an observer when the ChangeCallback is
  // called, so we need to re-register.
  storage_key->StartWatching(
      base::BindOnce(&BraveVpnDnsObserverService::OnRegistryKeyChanged,
                     weak_ptr_factory_.GetWeakPtr()));
}

void BraveVpnDnsObserverService::LockDNS() {
  auto old_dns_config =
      SystemNetworkContextManager::GetStubResolverConfigReader()
          ->GetSecureDnsConfiguration(false);

  local_state_->SetString(::prefs::kBraveVpnDnsConfig,
                          kCloudflareDnsProviderURL);

  // Trigger StubResolverConfigReader to see if it should override the settings
  // with kBraveVpnDnsConfig
  SystemNetworkContextManager::GetStubResolverConfigReader()
      ->UpdateNetworkService(false);
  auto new_dns_config =
      SystemNetworkContextManager::GetStubResolverConfigReader()
          ->GetSecureDnsConfiguration(false);

  if (old_dns_config.mode() != net::SecureDnsMode::kSecure) {
    if (AreConfigsEqual(old_dns_config, new_dns_config)) {
      ShowPolicyWarningMessage();
    } else {
      ShowVpnDnsSettingsNotificationDialog();
    }
  }
}

void BraveVpnDnsObserverService::OnConnectionStateChanged(
    brave_vpn::mojom::ConnectionState state) {
  vpn_state_ = state;
  if (state == brave_vpn::mojom::ConnectionState::CONNECTED) {
    if (IsDNSHelperLive()) {
      return;
    }
    LockDNS();
  } else if (state == brave_vpn::mojom::ConnectionState::DISCONNECTED) {
    UnlockDNS();
  }
}

}  // namespace brave_vpn
