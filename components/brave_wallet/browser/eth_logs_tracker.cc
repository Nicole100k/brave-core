/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_wallet/browser/eth_logs_tracker.h"

#include <string>
#include <utility>

namespace brave_wallet {

EthLogsTracker::EthLogsTracker(JsonRpcService* json_rpc_service)
    : json_rpc_service_(json_rpc_service) {
  DCHECK(json_rpc_service_);
}

EthLogsTracker::~EthLogsTracker() = default;

void EthLogsTracker::Start(base::TimeDelta interval) {
  timer_.Start(FROM_HERE, interval,
               base::BindRepeating(&EthLogsTracker::GetLogs,
                                   weak_factory_.GetWeakPtr()));
}

void EthLogsTracker::Stop() {
  timer_.Stop();
}

bool EthLogsTracker::IsRunning() const {
  return timer_.IsRunning();
}

void EthLogsTracker::AddSubscriber(const std::string& subscription_id,
                                   const base::Value& params) {
  eth_logs_subscription_info_.insert(
      std::pair<std::string, base::Value>(subscription_id, params.Clone()));
}

void EthLogsTracker::RemoveSubscriber(const std::string& subscription_id) {
  eth_logs_subscription_info_.erase(subscription_id);
}

void EthLogsTracker::AddObserver(EthLogsTracker::Observer* observer) {
  observers_.AddObserver(observer);
}

void EthLogsTracker::RemoveObserver(EthLogsTracker::Observer* observer) {
  observers_.RemoveObserver(observer);
}

void EthLogsTracker::GetLogs() {
  const auto chain_id = json_rpc_service_->GetChainId(mojom::CoinType::ETH);

  for (auto const& esi : std::as_const(eth_logs_subscription_info_)) {
    json_rpc_service_->EthGetLogs(
        chain_id, esi.second,
        base::BindOnce(&EthLogsTracker::OnGetLogs, weak_factory_.GetWeakPtr(),
                       esi.first));
  }
}

void EthLogsTracker::OnGetLogs(const std::string& subscription,
                               [[maybe_unused]] const std::vector<Log>& logs,
                               base::Value rawlogs,
                               mojom::ProviderError error,
                               const std::string& error_message) {
  if (error == mojom::ProviderError::kSuccess && rawlogs.is_dict()) {
    for (auto& observer : observers_)
      observer.OnLogsReceived(subscription, rawlogs.Clone());
  } else {
    LOG(ERROR) << "OnGetLogs failed";
  }
}

}  // namespace brave_wallet
