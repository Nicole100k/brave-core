/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/common/strings/string_conversions_util.h"

#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"

namespace ads {

namespace {

constexpr char kTrue[] = "true";
constexpr char kFalse[] = "false";

}  // namespace

std::string BoolToString(const bool value) {
  return value ? kTrue : kFalse;
}

std::vector<float> ConvertStringToVector(std::string string) {
  const std::vector<std::string> vector_string = base::SplitString(
      string, " ", base::TRIM_WHITESPACE, base::SPLIT_WANT_NONEMPTY);
  std::vector<float> vector;
  for (const std::string& element_string : vector_string) {
    double element;
    base::StringToDouble(element_string, &element);
    vector.push_back(static_cast<float>(element));
  }

  return vector;
}

std::string ConvertVectorToString(std::vector<float> vector) {
  size_t v_index = 0;
  std::vector<std::string> vector_as_string;
  while (v_index < vector.size()) {
    vector_as_string.push_back(base::NumberToString(vector.at(v_index)));
    ++v_index;
  }
  return base::JoinString(vector_as_string, " ");
}

}  // namespace ads
