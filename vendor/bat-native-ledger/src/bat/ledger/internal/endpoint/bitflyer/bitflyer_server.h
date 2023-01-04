/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_

#include <memory>

#include "bat/ledger/internal/endpoint/bitflyer/get_balance/get_balance_bitflyer.h"
#include "bat/ledger/internal/endpoint/bitflyer/post_oauth/post_oauth_bitflyer.h"
#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace endpoint {

class BitflyerServer {
 public:
  explicit BitflyerServer(LedgerImpl* ledger);
  ~BitflyerServer();

  bitflyer::GetBalance* get_balance() const;

  bitflyer::PostOauth* post_oauth() const;

 private:
  std::unique_ptr<bitflyer::GetBalance> get_balance_;
  std::unique_ptr<bitflyer::PostOauth> post_oauth_;
};

}  // namespace endpoint
}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_
