/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_VPN_BROWSER_CONNECTION_WIN_BRAVE_VPN_HELPER_BRAVE_VPN_HELPER_CONSTANTS_H_
#define BRAVE_COMPONENTS_BRAVE_VPN_BROWSER_CONNECTION_WIN_BRAVE_VPN_HELPER_BRAVE_VPN_HELPER_CONSTANTS_H_

#include <guiddef.h>

namespace brave_vpn {

constexpr char kBraveVpnHelperInstall[] = "install";
constexpr wchar_t kBraveVPNHelperExecutable[] = L"brave_vpn_helper.exe";
constexpr wchar_t kBraveVpnHelperLaunchCounterValue[] = L"launched";
// Repeating interval to check the connection is live.
constexpr int kCheckConnectionIntervalInSeconds = 3;

constexpr wchar_t kBraveVPNServiceFilter[] = L"Brave VPN Service DNS Filter";
constexpr wchar_t kBraveVpnHelperRegistryStoragePath[] =
    L"Software\\BraveSoftware\\Brave\\Vpn\\HelperService";
// 754b7cbd-cad3-474e-8d2c-054413fd4509
constexpr GUID kVpnDnsSublayerGUID = {
    0x754b7cbd,
    0xcad3,
    0x474e,
    {0x8d, 0x2c, 0x05, 0x44, 0x13, 0xfd, 0x45, 0x09}};

}  // namespace brave_vpn

#endif  // BRAVE_COMPONENTS_BRAVE_VPN_BROWSER_CONNECTION_WIN_BRAVE_VPN_HELPER_BRAVE_VPN_HELPER_CONSTANTS_H_
