// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/omnibox/browser/commander_provider.h"

#include <string>
#include <vector>

#include "base/memory/scoped_refptr.h"
#include "base/observer_list.h"
#include "base/test/scoped_feature_list.h"
#include "brave/components/commander/common/commander_frontend_delegate.h"
#include "brave/components/commander/common/commander_model.h"
#include "brave/components/commander/common/features.h"
#include "brave/components/omnibox/browser/brave_fake_autocomplete_provider_client.h"
#include "chrome/browser/ui/commander/commander_view_model.h"
#include "components/omnibox/browser/autocomplete_input.h"
#include "components/omnibox/browser/match_compare.h"
#include "components/omnibox/browser/test_scheme_classifier.h"
#include "omnibox_event.pb.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {
class FakeCommanderDelegate : public commander::CommanderFrontendDelegate {
 public:
  FakeCommanderDelegate() { SetInstance(this); }
  ~FakeCommanderDelegate() { SetInstance(nullptr); }

  void AddObserver(Observer* observer) override {
    observers_.AddObserver(observer);
  }
  void RemoveObserver(Observer* observer) override {
    observers_.RemoveObserver(observer);
  }

  void Notify(commander::CommanderModel model) {
    for (auto& observer : observers_) {
      observer.OnModelUpdated(model);
    }
  }

  void OnTextChanged(const std::u16string& text) override {
    last_text_ = text;
    notifies_++;
  }

  std::u16string last_text() { return last_text_; }
  int notifies() { return notifies_; }

 private:
  base::ObserverList<Observer> observers_;
  std::u16string last_text_ = u"";
  int notifies_ = 0;
};

AutocompleteInput CreateInput(std::u16string text) {
  return AutocompleteInput(text,
                           metrics::OmniboxEventProto::PageClassification::
                               OmniboxEventProto_PageClassification_NTP,
                           TestSchemeClassifier());
}
}  // namespace

class CommanderProviderTest : public testing::Test {
 public:
  CommanderProviderTest() {
    features_.InitAndEnableFeature(features::kBraveCommander);
  }

  void SetUp() override {
    provider_ =
        base::MakeRefCounted<commander::CommanderProvider>(&client_, nullptr);
  }

  FakeCommanderDelegate& delegate() { return fake_delegate_; }
  commander::CommanderProvider* provider() { return provider_.get(); }

 private:
  base::test::ScopedFeatureList features_;

  BraveFakeAutocompleteProviderClient client_;
  FakeCommanderDelegate fake_delegate_;
  scoped_refptr<commander::CommanderProvider> provider_;
};

TEST_F(CommanderProviderTest, EmptyTextDoesNotTriggerProvider) {
  provider()->Start(CreateInput(u""), false);
  EXPECT_EQ(0, delegate().notifies());
}
