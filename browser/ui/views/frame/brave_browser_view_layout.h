// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BROWSER_UI_VIEWS_FRAME_BRAVE_BROWSER_VIEW_LAYOUT_H_
#define BRAVE_BROWSER_UI_VIEWS_FRAME_BRAVE_BROWSER_VIEW_LAYOUT_H_

#include "chrome/browser/ui/views/frame/browser_view_layout.h"
class BraveBrowserViewLayout : public BrowserViewLayout {
 public:
  using BrowserViewLayout::BrowserViewLayout;
  ~BraveBrowserViewLayout() override;

  void set_vertical_tab_strip_host_view(views::View* view) {
    vertical_tab_strip_host_view_ = view;
  }

  // BrowserViewLayout overrides:
  void Layout(views::View* host) override;
  void LayoutSidePanelView(views::View* side_panel,
                           gfx::Rect& contents_container_bounds) override;
  int LayoutTabStripRegion(int top) override;

 private:
  raw_ptr<views::View> vertical_tab_strip_host_view_ = nullptr;
};

#endif  // BRAVE_BROWSER_UI_VIEWS_FRAME_BRAVE_BROWSER_VIEW_LAYOUT_H_
