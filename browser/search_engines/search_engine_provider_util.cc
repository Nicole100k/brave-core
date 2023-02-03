/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/search_engines/search_engine_provider_util.h"

#include <memory>
#include <string>
#include <vector>

#include "brave/browser/search_engines/pref_names.h"
#include "brave/components/search_engines/brave_prepopulated_engines.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/search_engines/template_url_service_factory.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_service.h"
#include "components/search_engines/search_engines_pref_names.h"
#include "components/search_engines/template_url_data.h"
#include "components/search_engines/template_url_data_util.h"
#include "components/search_engines/template_url_prepopulate_data.h"
#include "components/search_engines/template_url_service.h"

namespace brave {

namespace {

void SetBraveAsDefaultPrivateSearchProvider(PrefService* prefs) {
  auto data = TemplateURLPrepopulateData::GetPrepopulatedEngine(
      prefs,
      TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_BRAVE);
  DCHECK(data);
  prefs->SetString(prefs::kSyncedDefaultPrivateSearchProviderGUID,
                   data->sync_guid);
  prefs->SetDict(prefs::kSyncedDefaultPrivateSearchProviderData,
                 TemplateURLDataToDictionary(*data));
}

}  // namespace

bool IsRegionForQwant(Profile* profile) {
  return TemplateURLPrepopulateData::GetPrepopulatedDefaultSearch(
             profile->GetPrefs())
             ->prepopulate_id ==
         TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_QWANT;
}

void RegisterSearchEngineProviderPrefsForMigration(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(kUseAlternativePrivateSearchEngineProvider,
                                false);
  registry->RegisterBooleanPref(
      kShowAlternativePrivateSearchEngineProviderToggle, false);
}

void MigrateSearchEngineProviderPrefs(Profile* profile) {
  auto* preference = profile->GetPrefs()->FindPreference(
      prefs::kSyncedDefaultPrivateSearchProviderGUID);
  if (!preference->IsDefaultValue())
    return;

  const bool need_migrate =
      profile->GetPrefs()->GetBoolean(
          kShowAlternativePrivateSearchEngineProviderToggle) &&
      profile->GetPrefs()->GetBoolean(
          kUseAlternativePrivateSearchEngineProvider);

  if (!need_migrate)
    return;

  // If the user has been using DDG in private profile, set DDG as a initial
  // provider.
  std::vector<TemplateURLPrepopulateData::BravePrepopulatedEngineID>
      alt_search_providers = {
          TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO,
          TemplateURLPrepopulateData::PREPOPULATED_ENGINE_ID_DUCKDUCKGO_DE,
          TemplateURLPrepopulateData::
              PREPOPULATED_ENGINE_ID_DUCKDUCKGO_AU_NZ_IE};

  std::unique_ptr<TemplateURLData> data;
  for (const auto& id : alt_search_providers) {
    data = TemplateURLPrepopulateData::GetPrepopulatedEngine(
        profile->GetPrefs(), id);
    if (data)
      break;
  }

  // There should ALWAYS be one entry
  DCHECK(data);
  profile->GetPrefs()->SetString(prefs::kSyncedDefaultPrivateSearchProviderGUID,
                                 data->sync_guid);

  // From now on, user will not see DDG toggle button and can control search
  // provider for private window via settings.
  profile->GetPrefs()->ClearPref(
      kShowAlternativePrivateSearchEngineProviderToggle);
  profile->GetPrefs()->ClearPref(kUseAlternativePrivateSearchEngineProvider);
}

// TODO(simonhong): Split this to SetInitialProvder and UpdateProvider.
void SetDefaultPrivateSearchProvider(Profile* profile) {
  auto* prefs = profile->GetPrefs();
  auto* preference = prefs->FindPreference(
      prefs::kSyncedDefaultPrivateSearchProviderGUID);

  if (!preference)
    return;

  auto* service = TemplateURLServiceFactory::GetForProfile(profile);
  DCHECK(service->loaded());

  const std::string private_provider_guid = prefs->GetString(
      prefs::kSyncedDefaultPrivateSearchProviderGUID);

  // Set Brave as a private window's initial search provider.
  if (private_provider_guid.empty()) {
    SetBraveAsDefaultPrivateSearchProvider(prefs);
    return;
  }

  preference = prefs->FindPreference(prefs::kSyncedDefaultPrivateSearchProviderData);
  if (preference->IsDefaultValue()) {
    if (auto* url = service->GetTemplateURLForGUID(private_provider_guid)) {
      prefs->SetDict(prefs::kSyncedDefaultPrivateSearchProviderData,
                     TemplateURLDataToDictionary(url->data()));
    } else {
      SetBraveAsDefaultPrivateSearchProvider(prefs);
    }
    return;
  }

  // Check cached template url data is valid.
  auto private_url_data = TemplateURLDataFromDictionary(preference->GetValue()->GetDict());
  DCHECK_EQ(private_provider_guid, private_url_data->sync_guid);

  // If cached template url data is corrupted, set Brave.
  if (!private_url_data || (private_provider_guid != private_url_data->sync_guid)) {
    SetBraveAsDefaultPrivateSearchProvider(prefs);
    return;
  }

  // if previously used provider is not included in current provider list, add it.
  if (!service->GetTemplateURLForGUID(private_provider_guid)) {
    service->Add(std::make_unique<TemplateURL>(*private_url_data));
  }
}

void ClearDefaultPrivateSearchProvider(Profile* profile) {
  PrefService* prefs = profile->GetPrefs();
  prefs->ClearPref(prefs::kSyncedDefaultPrivateSearchProviderGUID);
  prefs->ClearPref(prefs::kSyncedDefaultPrivateSearchProviderData);
}

}  // namespace brave
