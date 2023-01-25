// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/webui/shortcuts_ui.h"
#include <utility>
#include "base/strings/utf_string_conversions.h"
#include "brave/app/command_utils.h"
#include "brave/browser/ui/webui/brave_webui_source.h"
#include "brave/components/shortcuts/browser/resources/grit/shortcuts_generated_map.h"
#include "brave/components/shortcuts/common/modifier_names.h"
#include "chrome/browser/ui/views/accelerator_table.h"
#include "components/grit/brave_components_resources.h"
#include "content/public/browser/web_ui_controller.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/events/keycodes/keysym_to_unicode.h"

namespace shortcuts {
ShortcutsUI::ShortcutsUI(content::WebUI* web_ui, const std::string& name)
    : content::WebUIController(web_ui) {
  // auto* source =
  CreateAndAddWebUIDataSource(web_ui, name, kShortcutsGenerated,
                              kShortcutsGeneratedSize, IDR_SHORTCUTS_HTML);
}

ShortcutsUI::~ShortcutsUI() = default;

void ShortcutsUI::BindInterface(
    mojo::PendingReceiver<ShortcutsService> pending_receiver) {
  if (receiver_.is_bound())
    receiver_.reset();

  receiver_.Bind(std::move(pending_receiver));
}

void ShortcutsUI::GetCommands(GetCommandsCallback callback) {
  auto command_ids = shortcuts::GetCommands();
  auto accelerators = GetAcceleratorList();

  std::vector<CommandPtr> result;
  for (const auto& command_id : command_ids) {
    auto command = Command::New();
    command->id = command_id;
    command->name = shortcuts::GetCommandName(command_id);

    for (const auto& entry : accelerators) {
      if (command_id != entry.command_id)
        continue;

      ui::Accelerator accel(entry.keycode, entry.modifiers);

      char keycode = toupper(ui::GetUnicodeCharacterFromXKeySym(entry.keycode));
      auto a = Accelerator::New();
      a->keycode = keycode;
      a->modifiers = shortcuts::GetModifierName(entry.modifiers);

      if (!a->modifiers.size() || a->keycode.empty())
        continue;
      command->accelerators.push_back(std::move(a));
    }
    result.push_back(std::move(command));
  }

  std::move(callback).Run(std::move(result));
}

WEB_UI_CONTROLLER_TYPE_IMPL(ShortcutsUI)

}  // namespace shortcuts
