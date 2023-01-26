// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/webui/commands_ui.h"

#include <utility>

#include "base/strings/utf_string_conversions.h"
#include "brave/app/command_utils.h"
#include "brave/browser/ui/views/frame/brave_browser_view.h"
#include "brave/browser/ui/webui/brave_webui_source.h"
#include "brave/components/commands/browser/resources/grit/commands_generated_map.h"
#include "brave/components/commands/common/commands.mojom.h"
#include "brave/components/commands/common/key_names.h"
#include "chrome/browser/ui/browser_commands.h"
#include "chrome/browser/ui/browser_finder.h"
#include "components/grit/brave_components_resources.h"
#include "content/public/browser/web_ui_controller.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/events/event_constants.h"
#include "ui/events/keycodes/keysym_to_unicode.h"

namespace commands {
CommandsUI::CommandsUI(content::WebUI* web_ui, const std::string& name)
    : content::WebUIController(web_ui),
      browser_view_(static_cast<BraveBrowserView*>(
          chrome::FindBrowserWithWebContents(web_ui->GetWebContents())
              ->window())) {
  // auto* source =
  CreateAndAddWebUIDataSource(web_ui, name, kCommandsGenerated,
                              kCommandsGeneratedSize, IDR_COMMANDS_HTML);
}

CommandsUI::~CommandsUI() = default;

void CommandsUI::BindInterface(
    mojo::PendingReceiver<CommandsService> pending_receiver) {
  if (receiver_.is_bound())
    receiver_.reset();

  receiver_.Bind(std::move(pending_receiver));
}

void CommandsUI::GetCommands(GetCommandsCallback callback) {
  auto command_ids = commands::GetCommands();
  auto accelerated_commands = browser_view_->GetAcceleratedCommands();

  std::vector<CommandPtr> result;
  for (const auto& command_id : command_ids) {
    auto command = Command::New();
    command->id = command_id;
    command->name = commands::GetCommandName(command_id);

    auto it = accelerated_commands.find(command_id);
    if (it != accelerated_commands.end()) {
      for (const auto& accel : it->second) {
        auto a = Accelerator::New();
        a->keycode = commands::GetKeyName(accel.key_code());
        a->modifiers = commands::GetModifierName(accel.modifiers());

        if ((!a->modifiers.size() && accel.modifiers() != ui::EF_NONE) ||
            a->keycode.empty())
          continue;
        command->accelerators.push_back(std::move(a));
      }
    }
    result.push_back(std::move(command));
  }

  std::move(callback).Run(std::move(result));
}

void CommandsUI::TryExecuteCommand(uint32_t command_id) {
  chrome::ExecuteCommand(browser_view_->browser(), command_id);
}

WEB_UI_CONTROLLER_TYPE_IMPL(CommandsUI)

}  // namespace commands
