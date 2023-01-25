// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BROWSER_UI_WEBUI_SHORTCUTS_UI_H_
#define BRAVE_BROWSER_UI_WEBUI_SHORTCUTS_UI_H_

#include <memory>
#include <string>

#include "base/memory/weak_ptr.h"
#include "brave/components/playlist/common/mojom/playlist.mojom.h"
#include "brave/components/shortcuts/common/shortcuts.mojom.h"
#include "content/public/browser/web_ui_controller.h"
#include "content/public/browser/webui_config.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/receiver_set.h"
#include "ui/webui/mojo_bubble_web_ui_controller.h"
#include "ui/webui/untrusted_web_ui_controller.h"

namespace content {
class BrowserContext;
}  // namespace content

class GURL;

namespace shortcuts {

class ShortcutsUI : public content::WebUIController, public ShortcutsService {
 public:
  ShortcutsUI(content::WebUI* web_ui, const std::string& host);
  ~ShortcutsUI() override;
  ShortcutsUI(const ShortcutsUI&) = delete;
  ShortcutsUI& operator=(const ShortcutsUI&) = delete;

  void BindInterface(mojo::PendingReceiver<ShortcutsService> pending_receiver);

  // ShortcutsService:
  void GetCommands(GetCommandsCallback callback) override;

 private:
  mojo::Receiver<ShortcutsService> receiver_{this};

  WEB_UI_CONTROLLER_TYPE_DECL();
};

}  // namespace shortcuts

#endif  // BRAVE_BROWSER_UI_WEBUI_SHORTCUTS_UI_H_
