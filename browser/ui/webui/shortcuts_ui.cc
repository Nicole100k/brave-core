// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/webui/shortcuts_ui.h"
#include "brave/browser/ui/webui/brave_webui_source.h"
#include "components/grit/brave_components_resources.h"
#include "content/public/browser/web_ui_controller.h"
#include "brave/components/shortcuts/browser/resources/grit/shortcuts_generated_map.h"

namespace shortcuts {
ShortcutsUI::ShortcutsUI(content::WebUI* web_ui, const std::string& name)
    : content::WebUIController(web_ui) {
  // auto* source =
      CreateAndAddWebUIDataSource(web_ui, name, kShortcutsGenerated,
                                  kShortcutsGeneratedSize, IDR_SHORTCUTS_HTML);
}

ShortcutsUI::~ShortcutsUI() = default;

WEB_UI_CONTROLLER_TYPE_IMPL(ShortcutsUI)

}  // namespace shortcuts
