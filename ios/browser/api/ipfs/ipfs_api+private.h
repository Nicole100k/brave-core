/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_IOS_BROWSER_API_IPFS_IPFS_API_PRIVATE_
#define BRAVE_IOS_BROWSER_API_IPFS_IPFS_API_PRIVATE_

#import <Foundation/Foundation.h>

#include "brave/ios/browser/api/ipfs/ipfs_api.h"

NS_ASSUME_NONNULL_BEGIN

class ChromeBrowserState;

@interface IpfsAPI (Private)
- (instancetype)initWithBrowserState:(ChromeBrowserState*)mainBrowserState;
@end

NS_ASSUME_NONNULL_END

#endif  // BRAVE_IOS_BROWSER_API_IPFS_IPFS_API_PRIVATE_
