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
#include "brave/components/commander/common/commander_url.h"
#include "brave/components/commander/common/constants.h"
#include "brave/components/commander/common/features.h"
#include "brave/components/omnibox/browser/brave_fake_autocomplete_provider_client.h"
#include "components/omnibox/browser/autocomplete_input.h"
#include "components/omnibox/browser/autocomplete_match.h"
#include "components/omnibox/browser/autocomplete_provider_listener.h"
#include "components/omnibox/browser/match_compare.h"
#include "components/omnibox/browser/test_scheme_classifier.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/googletest/src/googletest/include/gtest/gtest.h"

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
  EXPECT_EQ(0u, provider()->matches().size());
}

TEST_F(CommanderProviderTest, NonPrefixedTextDoesNotTriggerProvider) {
  provider()->Start(CreateInput(u"Hello"), false);
  EXPECT_EQ(0, delegate().notifies());
  EXPECT_EQ(0u, provider()->matches().size());
}

TEST_F(CommanderProviderTest, PrefixTriggersProvider) {
  provider()->Start(CreateInput(commander::kCommandPrefix), false);
  EXPECT_EQ(1, delegate().notifies());
  EXPECT_EQ(u"", delegate().last_text());
  EXPECT_EQ(0u, provider()->matches().size());
}

TEST_F(CommanderProviderTest, PrefixedCommandTriggersProvider) {
  provider()->Start(
      CreateInput(commander::kCommandPrefix + std::u16string(u"Hello")), false);
  EXPECT_EQ(1, delegate().notifies());
  EXPECT_EQ(u"Hello", delegate().last_text());
  EXPECT_EQ(0u, provider()->matches().size());
}

TEST_F(CommanderProviderTest, PrefixWhiteSpaceIsStripped) {
  provider()->Start(
      CreateInput(commander::kCommandPrefix + std::u16string(u"  Hello")),
      false);
  EXPECT_EQ(1, delegate().notifies());
  EXPECT_EQ(u"Hello", delegate().last_text());
  EXPECT_EQ(0u, provider()->matches().size());
}

TEST_F(CommanderProviderTest, ItemsAreConvertedToMatches) {
  provider()->Start(CreateInput(u":> Hello World"), false);

  commander::CommanderModel model;
  model.result_set_id = 1;
  model.items.push_back(commander::CommandItemModel(u"First", {}, u"Ctrl+F"));
  model.items.push_back(commander::CommandItemModel(u"Second", {}, u"Ctrl+S"));

  delegate().Notify(model);

  EXPECT_EQ(2u, provider()->matches().size());

  EXPECT_EQ(u":> First", provider()->matches()[0].description);
  EXPECT_EQ(u"Ctrl+F", provider()->matches()[0].contents);

  EXPECT_EQ(u":> Second", provider()->matches()[1].description);
  EXPECT_EQ(u"Ctrl+S", provider()->matches()[1].contents);

  int command_index = 0;
  for (const auto& match : provider()->matches()) {
    // As we haven't specified a prompt, none of the matches should have
    // additional_text.
    EXPECT_EQ(u"", match.additional_text);
    // All matches swap the contents & description, so that the command displays
    // on the left and the shortcut (if any) on the right.
    EXPECT_TRUE(match.swap_contents_and_description);
    // All matches should be allowed to be the default, so when the user presses
    // enter, the top command is executed.
    EXPECT_TRUE(match.allowed_to_be_default_match);
    // fill_into_edit should be the same as whatever the last input was, so
    // scrolling through the commands doesn't affect what the user typed.
    EXPECT_EQ(u":> Hello World", match.fill_into_edit);
    // Check the urls are what we expect.
    EXPECT_EQ(commander::GetCommandURL(command_index++, model.result_set_id),
              match.destination_url);
  }
}

TEST_F(CommanderProviderTest, PromptingForMoreInputSetsAnnotation) {
  commander::CommanderModel model;
  model.action = commander::CommanderModel::kPrompt;
  model.prompt_text = u"What thing?";
  model.items.push_back(commander::CommandItemModel(u"Foo", {}, u""));
  delegate().Notify(model);

  EXPECT_EQ(1u, provider()->matches().size());
  EXPECT_EQ(u"What thing?", provider()->matches()[0].additional_text);
  EXPECT_EQ(u":> Foo", provider()->matches()[0].description);

  model = commander::CommanderModel();
  model.items.push_back(commander::CommandItemModel(u"Bar", {}, u""));
  delegate().Notify(model);

  // Should keep the additional_text until it's cleared or a new prompt is made.
  EXPECT_EQ(1u, provider()->matches().size());
  EXPECT_EQ(u"What thing?", provider()->matches()[0].additional_text);
  EXPECT_EQ(u":> Bar", provider()->matches()[0].description);

  model = commander::CommanderModel();
  model.action = commander::CommanderModel::kPrompt;
  model.prompt_text = u"New thing";
  model.items.push_back(commander::CommandItemModel(u"Frob", {}, u""));
  delegate().Notify(model);

  EXPECT_EQ(1u, provider()->matches().size());
  EXPECT_EQ(u"New thing", provider()->matches()[0].additional_text);
  EXPECT_EQ(u":> Frob", provider()->matches()[0].description);
}

TEST_F(CommanderProviderTest, CloseActionRemovesPrompt) {
  commander::CommanderModel model;
  model.action = commander::CommanderModel::kPrompt;
  model.prompt_text = u"What thing?";
  delegate().Notify(model);
  EXPECT_EQ(0u, provider()->matches().size());

  model = commander::CommanderModel();
  model.action = commander::CommanderModel::kClose;
  delegate().Notify(model);
  EXPECT_EQ(0u, provider()->matches().size());

  model = commander::CommanderModel();
  model.items.push_back(commander::CommandItemModel(u"Foo", {}, u""));
  delegate().Notify(model);
  EXPECT_EQ(1u, provider()->matches().size());
  EXPECT_EQ(u"", provider()->matches()[0].additional_text);
}
