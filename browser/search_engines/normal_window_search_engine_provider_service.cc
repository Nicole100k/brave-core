/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/search_engines/normal_window_search_engine_provider_service.h"

#include "base/bind.h"
#include "brave/browser/search_engines/search_engine_provider_util.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/search_engines/template_url_service_factory.h"
#include "components/search_engines/template_url_service.h"
#include "components/search_engines/search_engines_pref_names.h"

NormalWindowSearchEngineProviderService::
    NormalWindowSearchEngineProviderService(Profile* profile)
    : profile_(profile) {
  private_search_provider_guid_.Init(
      prefs::kSyncedDefaultPrivateSearchProviderGUID,
      profile_->GetPrefs(),
      base::BindRepeating(
          &NormalWindowSearchEngineProviderService::OnPreferenceChanged,
          base::Unretained(this)));

  auto* service = TemplateURLServiceFactory::GetForProfile(profile_);
  if (service->loaded()) {
    brave::SetDefaultPrivateSearchProvider(profile_);
    return;
  }

  // Using Unretained safe with subscription_.
  template_url_service_subscription_ =
      service->RegisterOnLoadedCallback(base::BindOnce(
          &NormalWindowSearchEngineProviderService::OnTemplateURLServiceLoaded,
          base::Unretained(this), profile));
}

NormalWindowSearchEngineProviderService::
    ~NormalWindowSearchEngineProviderService() = default;

void NormalWindowSearchEngineProviderService::OnTemplateURLServiceLoaded(
    Profile* profile) {
  template_url_service_subscription_ = {};
  brave::SetDefaultPrivateSearchProvider(profile_);
}

void NormalWindowSearchEngineProviderService::OnPreferenceChanged(
    const std::string& pref_name) {
  brave::SetDefaultPrivateSearchProvider(profile_);
}
