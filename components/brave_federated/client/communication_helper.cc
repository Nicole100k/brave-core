/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_federated/client/communication_helper.h"

#include "base/json/json_writer.h"
#include "base/strings/string_util.h"
#include "base/values.h"

namespace {
// TODO(lminto): Create this wiki url
constexpr char kWikiUrl[] =
    "https://github.com/brave/brave-browser/wiki/Federated-Learning";

}  // namespace

namespace brave_federated {

std::string BuildGetTasksPayload() {
  base::Value::Dict root;
  root.Set("wiki-link", kWikiUrl);

  std::string result;
  base::JSONWriter::Write(root, &result);

  return result;
}

std::string BuildPostTaskResultsPayload() {
  base::Value::Dict root;
  root.Set("wiki-link", kWikiUrl);

  std::string result;
  base::JSONWriter::Write(root, &result);

  return result;
}

}  // namespace brave_federated
