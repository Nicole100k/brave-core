/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include <utility>

#include "base/strings/string_number_conversions.h"
#include "base/strings/stringprintf.h"
#include "bat/ledger/internal/database/database_external_transactions.h"
#include "bat/ledger/internal/database/database_util.h"
#include "bat/ledger/internal/ledger_impl.h"

namespace ledger::database {

constexpr char kTableName[] = "external_transactions";

DatabaseExternalTransactions::DatabaseExternalTransactions(LedgerImpl* ledger)
    : DatabaseTable(ledger) {}

DatabaseExternalTransactions::~DatabaseExternalTransactions() = default;

void DatabaseExternalTransactions::Insert(
    mojom::ExternalTransactionPtr external_transaction,
    ledger::ResultCallback callback) {
  if (!external_transaction) {
    BLOG(0, "external_transaction is null!");
    return std::move(callback).Run(mojom::Result::LEDGER_ERROR);
  }

  auto command = mojom::DBCommand::New();
  command->type = mojom::DBCommand::Type::RUN;
  command->command = base::StringPrintf(
      R"(
        INSERT INTO %s (transaction_id, contribution_id, destination, amount)
        VALUES(?, ?, ?, ?)
      )",
      kTableName);
  BindString(command.get(), 0, external_transaction->transaction_id);
  BindString(command.get(), 1, external_transaction->contribution_id);
  BindString(command.get(), 2, external_transaction->destination);
  BindString(command.get(), 3, external_transaction->amount);

  auto transaction = mojom::DBTransaction::New();
  transaction->commands.push_back(std::move(command));

  ledger_->RunDBTransaction(
      std::move(transaction),
      base::BindOnce(&DatabaseExternalTransactions::OnInsert,
                     base::Unretained(this), std::move(callback)));
}

void DatabaseExternalTransactions::OnInsert(
    ledger::ResultCallback callback,
    mojom::DBCommandResponsePtr response) {
  std::move(callback).Run(
      response &&
              response->status == mojom::DBCommandResponse::Status::RESPONSE_OK
          ? mojom::Result::LEDGER_OK
          : mojom::Result::LEDGER_ERROR);
}

void DatabaseExternalTransactions::GetTransaction(
    const std::string& contribution_id,
    const std::string& destination,
    GetExternalTransactionCallback callback) {
  auto command = mojom::DBCommand::New();
  command->type = mojom::DBCommand::Type::READ;
  command->command = base::StringPrintf(
      R"(
        SELECT transaction_id, contribution_id, destination, amount
        FROM %s
        WHERE contribution_id = ? AND destination = ?
      )",
      kTableName);
  command->record_bindings = {mojom::DBCommand::RecordBindingType::STRING_TYPE,
                              mojom::DBCommand::RecordBindingType::STRING_TYPE,
                              mojom::DBCommand::RecordBindingType::STRING_TYPE,
                              mojom::DBCommand::RecordBindingType::STRING_TYPE};
  BindString(command.get(), 0, contribution_id);
  BindString(command.get(), 1, destination);

  auto transaction = mojom::DBTransaction::New();
  transaction->commands.push_back(std::move(command));

  ledger_->RunDBTransaction(
      std::move(transaction),
      base::BindOnce(&DatabaseExternalTransactions::OnGetTransaction,
                     base::Unretained(this), std::move(callback)));
}

void DatabaseExternalTransactions::OnGetTransaction(
    GetExternalTransactionCallback callback,
    mojom::DBCommandResponsePtr response) {
  if (!response ||
      response->status != mojom::DBCommandResponse::Status::RESPONSE_OK) {
    BLOG(0, "Failed to get external transaction!");
    return std::move(callback).Run(absl::nullopt);
  }

  const auto& records = response->result->get_records();
  if (records.empty()) {
    return std::move(callback).Run(nullptr);
  }

  DCHECK_EQ(records.size(), 1ull);
  if (records.size() != 1) {
    BLOG(0, "Failed to get external transaction!");
    return std::move(callback).Run(absl::nullopt);
  }

  auto transaction_id = GetStringColumn(records[0].get(), 0);
  auto contribution_id = GetStringColumn(records[0].get(), 1);
  auto destination = GetStringColumn(records[0].get(), 2);
  auto amount = GetStringColumn(records[0].get(), 3);

  if (transaction_id.empty() || contribution_id.empty() ||
      destination.empty() || amount.empty()) {
    BLOG(0, "Failed to get external transaction!");
    return std::move(callback).Run(absl::nullopt);
  }

  if (double value = 0.0; !base::StringToDouble(amount, &value)) {
    BLOG(0, "Failed to get external transaction!");
    return std::move(callback).Run(absl::nullopt);
  }

  std::move(callback).Run(mojom::ExternalTransaction::New(
      std::move(transaction_id), std::move(contribution_id),
      std::move(destination), std::move(amount)));
}

}  // namespace ledger::database
