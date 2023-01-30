/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_CHROMIUM_SRC_CHROME_COMMON_CHROME_CONTENT_CLIENT_H_
#define BRAVE_CHROMIUM_SRC_CHROME_COMMON_CHROME_CONTENT_CLIENT_H_

#define kPDFExtensionPluginPath     \
  kPDFExtensionPluginPath_Unused[]; \
  static const char kPDFExtensionPluginPath

#define kPDFInternalPluginPath     \
  kPDFInternalPluginPath_Unused[]; \
  static const char kPDFInternalPluginPath

#include "src/chrome/common/chrome_content_client.h"

#undef kPDFExtensionPluginPath
#undef kPDFInternalPluginPath

#endif  // BRAVE_CHROMIUM_SRC_CHROME_COMMON_CHROME_CONTENT_CLIENT_H_
