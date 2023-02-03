/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/p3a/brave_p3a_metric_log_store.h"

#include <vector>

#include "base/check_op.h"
#include "base/logging.h"
#include "base/metrics/histogram_macros.h"
#include "base/rand_util.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "brave/components/p3a/brave_p3a_uploader.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"
#include "components/prefs/scoped_user_pref_update.h"

namespace brave {

namespace {
constexpr char kTypicalJsonLogPrefName[] = "p3a.logs";
constexpr char kSlowJsonLogPrefName[] = "p3a.logs_slow";
constexpr char kExpressJsonLogPrefName[] = "p3a.logs_express";
constexpr char kStarPrepPrefName[] = "p3a.logs.star_prep";
constexpr char kLogValueKey[] = "value";
constexpr char kLogSentKey[] = "sent";
constexpr char kLogTimestampKey[] = "timestamp";

void RecordSentAnswersCount(uint64_t answers_count) {
  int answer = 0;
  if (1 <= answers_count && answers_count < 5) {
    answer = 1;
  } else if (5 <= answers_count && answers_count < 10) {
    answer = 2;
  } else if (10 <= answers_count) {
    answer = 3;
  }
  UMA_HISTOGRAM_EXACT_LINEAR("Brave.P3A.SentAnswersCount", answer, 3);
}

bool IsMetricP2A(const std::string& histogram_name) {
  return base::StartsWith(histogram_name, "Brave.P2A",
                          base::CompareCase::SENSITIVE);
}

bool IsMetricCreative(const std::string& histogram_name) {
  return base::StartsWith(histogram_name, kCreativeMetricPrefix,
                          base::CompareCase::SENSITIVE);
}

std::string GetUploadType(const std::string& histogram_name) {
  if (IsMetricP2A(histogram_name)) {
    return kP2AUploadType;
  } else if (IsMetricCreative(histogram_name)) {
    return kP3ACreativeUploadType;
  }
  return kP3AUploadType;
}

}  // namespace

BraveP3AMetricLogStore::BraveP3AMetricLogStore(Delegate* delegate,
                                               PrefService* local_state,
                                               bool is_star,
                                               MetricLogType type)
    : delegate_(delegate),
      local_state_(local_state),
      type_(type),
      is_star_(is_star) {
  DCHECK(delegate_);
  DCHECK(local_state);
}

BraveP3AMetricLogStore::~BraveP3AMetricLogStore() = default;

void BraveP3AMetricLogStore::RegisterPrefs(PrefRegistrySimple* registry) {
  registry->RegisterDictionaryPref(kTypicalJsonLogPrefName);
  registry->RegisterDictionaryPref(kExpressJsonLogPrefName);
  registry->RegisterDictionaryPref(kSlowJsonLogPrefName);
  registry->RegisterDictionaryPref(kStarPrepPrefName);
}

const char* BraveP3AMetricLogStore::GetPrefName() const {
  if (is_star_) {
    return kStarPrepPrefName;
  } else {
    switch (type_) {
      case MetricLogType::kTypical:
        return kTypicalJsonLogPrefName;
      case MetricLogType::kExpress:
        return kExpressJsonLogPrefName;
      case MetricLogType::kSlow:
        return kSlowJsonLogPrefName;
    }
  }
}

void BraveP3AMetricLogStore::UpdateValue(const std::string& histogram_name,
                                         uint64_t value) {
  if (is_star_) {
    if (IsMetricP2A(histogram_name) || IsMetricCreative(histogram_name)) {
      // Only non-creative P3A metrics are currently supported for STAR.
      return;
    }
  }
  LogEntry& entry = log_[histogram_name];
  entry.value = value;

  if (!entry.sent) {
    DCHECK(entry.sent_timestamp.is_null());
    unsent_entries_.insert(histogram_name);
  }

  // Update the persistent value.
  ScopedDictPrefUpdate update(local_state_, GetPrefName());
  update->SetByDottedPath(base::JoinString({histogram_name, kLogValueKey}, "."),
                          base::NumberToString(value));
  update->SetByDottedPath(base::JoinString({histogram_name, kLogSentKey}, "."),
                          entry.sent);
}

void BraveP3AMetricLogStore::RemoveValueIfExists(
    const std::string& histogram_name) {
  log_.erase(histogram_name);
  unsent_entries_.erase(histogram_name);

  // Update the persistent value.
  ScopedDictPrefUpdate(local_state_, GetPrefName())->Remove(histogram_name);

  if (has_staged_log() && staged_entry_key_ == histogram_name) {
    staged_entry_key_.clear();
    staged_log_.clear();
  }
}

void BraveP3AMetricLogStore::ResetUploadStamps() {
  // Clear log entries flags.
  ScopedDictPrefUpdate update(local_state_, GetPrefName());
  for (auto& pair : log_) {
    if (pair.second.sent) {
      DCHECK(!pair.second.sent_timestamp.is_null());
      DCHECK(!unsent_entries_.contains(pair.first));

      pair.second.ResetSentState();

      // Update persistent values.
      update->SetByDottedPath(base::JoinString({pair.first, kLogSentKey}, "."),
                              pair.second.sent);
      update->SetByDottedPath(
          base::JoinString({pair.first, kLogTimestampKey}, "."),
          pair.second.sent_timestamp.ToDoubleT());
    }
  }

  // Only record the sent answers count metric for weekly metrics
  if (type_ == MetricLogType::kTypical) {
    RecordSentAnswersCount(log_.size() - unsent_entries_.size());
  }

  // Rebuild the unsent set.
  unsent_entries_.clear();
  for (const auto& pair : log_) {
    unsent_entries_.insert(pair.first);
  }
}

bool BraveP3AMetricLogStore::has_unsent_logs() const {
  return !unsent_entries_.empty();
}

bool BraveP3AMetricLogStore::has_staged_log() const {
  return !staged_entry_key_.empty();
}

const std::string& BraveP3AMetricLogStore::staged_log() const {
  DCHECK(!staged_entry_key_.empty());
  auto iter = log_.find(staged_entry_key_);
  DCHECK(iter != log_.end());

  return staged_log_;
}

std::string BraveP3AMetricLogStore::staged_log_type() const {
  DCHECK(!staged_entry_key_.empty());
  auto iter = log_.find(staged_entry_key_);
  DCHECK(iter != log_.end());

  return GetUploadType(iter->first);
}

const std::string& BraveP3AMetricLogStore::staged_log_key() const {
  DCHECK(!staged_entry_key_.empty());

  return staged_entry_key_;
}

const std::string& BraveP3AMetricLogStore::staged_log_hash() const {
  NOTREACHED();
  return staged_log_hash_;
}

const std::string& BraveP3AMetricLogStore::staged_log_signature() const {
  NOTREACHED();
  return staged_log_signature_;
}

absl::optional<uint64_t> BraveP3AMetricLogStore::staged_log_user_id() const {
  NOTREACHED();
  return absl::nullopt;
}

void BraveP3AMetricLogStore::StageNextLog() {
  // Stage the next item.
  DCHECK(has_unsent_logs());
  uint64_t rand_idx = base::RandGenerator(unsent_entries_.size());
  staged_entry_key_ = *(unsent_entries_.begin() + rand_idx);
  DCHECK(!log_.find(staged_entry_key_)->second.sent);

  uint64_t staged_entry_value = log_[staged_entry_key_].value;
  staged_log_ =
      delegate_->SerializeLog(staged_entry_key_, staged_entry_value, type_,
                              is_star_, GetUploadType(staged_entry_key_));

  VLOG(2) << "BraveP3AMetricLogStore::StageNextLog: staged "
          << staged_entry_key_;
}

void BraveP3AMetricLogStore::DiscardStagedLog() {
  if (!has_staged_log()) {
    return;
  }

  // Mark previous staged log as sent.
  auto log_iter = log_.find(staged_entry_key_);
  DCHECK(log_iter != log_.end());
  log_iter->second.MarkAsSent();

  // Update the persistent value.
  ScopedDictPrefUpdate update(local_state_, GetPrefName());
  update->SetByDottedPath(base::JoinString({log_iter->first, kLogSentKey}, "."),
                          log_iter->second.sent);
  update->SetByDottedPath(
      base::JoinString({log_iter->first, kLogTimestampKey}, "."),
      log_iter->second.sent_timestamp.ToDoubleT());

  // Erase the entry from the unsent queue.
  auto unsent_entries_iter = unsent_entries_.find(staged_entry_key_);
  DCHECK(unsent_entries_iter != unsent_entries_.end());
  unsent_entries_.erase(unsent_entries_iter);

  staged_entry_key_.clear();
  staged_log_.clear();
}

void BraveP3AMetricLogStore::MarkStagedLogAsSent() {}

void BraveP3AMetricLogStore::TrimAndPersistUnsentLogs(
    bool overwrite_in_memory_store) {
  NOTREACHED();
}

void BraveP3AMetricLogStore::LoadPersistedUnsentLogs() {
  DCHECK(log_.empty());
  DCHECK(unsent_entries_.empty());

  std::vector<std::string> metrics_to_remove;

  ScopedDictPrefUpdate update(local_state_, GetPrefName());
  for (const auto [name, value] : update.Get()) {
    LogEntry entry;
    // Check if the metric is obsolete.
    if (!delegate_->IsActualMetric(name)) {
      // Drop it from the local state.
      metrics_to_remove.push_back(name);
      continue;
    }
    // Value.
    const base::Value::Dict& dict = value.GetDict();
    if (const std::string* v = dict.FindString(kLogValueKey)) {
      if (!base::StringToUint64(*v, &entry.value)) {
        return;
      }
    } else {
      return;
    }

    // Sent flag.
    if (auto v = dict.FindBool(kLogSentKey)) {
      entry.sent = *v;
    } else {
      return;
    }

    // Timestamp.
    if (auto v = dict.FindDouble(kLogTimestampKey)) {
      entry.sent_timestamp = base::Time::FromDoubleT(*v);
      if ((entry.sent && entry.sent_timestamp.is_null()) ||
          (!entry.sent && !entry.sent_timestamp.is_null())) {
        return;
      }
    } else {
      // Sometimes we do not persist empty timestamps, so it is ok.
    }

    log_[name] = entry;
    if (!entry.sent) {
      unsent_entries_.insert(name);
    }
  }

  for (const std::string& name : metrics_to_remove) {
    update->Remove(name);
  }
}

}  // namespace brave
