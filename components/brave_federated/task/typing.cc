/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_federated/task/typing.h"
#include "brave/components/brave_federated/task/model.h"

namespace brave_federated {

Task::Task(int task_id, TaskType type, std::string token)
    : task_id_(task_id), type_(type), token_(token) {}

Task::~Task() = default;

int Task::GetId() {
  return task_id_;
}

TaskType Task::GetType() {
  return type_;
}

std::string Task::GetToken() {
  return token_;
}

TaskResult::TaskResult(Task task, PerformanceReport report)
    : task_(task), report_(report) {}

Task TaskResult::GetTask() {
  return task_;
}

PerformanceReport TaskResult::GetReport() {
  return report_;
}

TaskResult::~TaskResult() = default;

TaskResultResponse::TaskResultResponse(bool success) : success_(success) {}

bool TaskResultResponse::IsSuccessful() {
  return success_;
}

TaskResultResponse::~TaskResultResponse() = default;

}  // namespace brave_federated
