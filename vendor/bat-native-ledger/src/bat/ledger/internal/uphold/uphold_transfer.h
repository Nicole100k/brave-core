/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_UPHOLD_UPHOLD_TRANSFER_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_UPHOLD_UPHOLD_TRANSFER_H_

#include <map>
#include <memory>
#include <string>

#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace endpoint {
class UpholdServer;
}

namespace uphold {

class UpholdTransfer {
 public:
  explicit UpholdTransfer(LedgerImpl* ledger);

  ~UpholdTransfer();

  void Start(const Transaction&, client::TransactionCallback);

 private:
  void OnCreateTransaction(mojom::Result,
                           const std::string& id,
                           client::TransactionCallback);

  void CommitTransaction(
      const std::string& transaction_id,
      client::TransactionCallback callback);

  void OnCommitTransaction(mojom::Result,
                           const std::string& transaction_id,
                           client::TransactionCallback);

  LedgerImpl* ledger_;  // NOT OWNED
  std::unique_ptr<endpoint::UpholdServer> uphold_server_;
};

}  // namespace uphold
}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_UPHOLD_UPHOLD_TRANSFER_H_
