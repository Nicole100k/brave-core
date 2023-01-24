
// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/app/command_utils.h"

#include "base/notreached.h"

#include "chrome/app/chrome_command_ids.h"
#include "brave/app/brave_command_ids.h"

namespace shortcuts {
std::vector<uint16_t> GetCommands() {
  return std::vector<uint16_t> {IDC_BACK, IDC_FORWARD, IDC_RELOAD, IDC_HOME, IDC_OPEN_CURRENT_URL, IDC_STOP, IDC_RELOAD_BYPASSING_CACHE, IDC_RELOAD_CLEARING_CACHE, IDC_NEW_WINDOW, IDC_NEW_INCOGNITO_WINDOW, IDC_PIN_TO_START_SCREEN, IDC_CLOSE_WINDOW, IDC_ALWAYS_ON_TOP, IDC_NEW_TAB, IDC_CLOSE_TAB, IDC_SELECT_NEXT_TAB, IDC_SELECT_PREVIOUS_TAB, IDC_SELECT_TAB_0, IDC_SELECT_TAB_1, IDC_SELECT_TAB_2, IDC_SELECT_TAB_3, IDC_SELECT_TAB_4, IDC_SELECT_TAB_5, IDC_SELECT_TAB_6, IDC_SELECT_TAB_7, IDC_SELECT_LAST_TAB, IDC_DUPLICATE_TAB, IDC_RESTORE_TAB, IDC_SHOW_AS_TAB, IDC_FULLSCREEN, IDC_EXIT, IDC_MOVE_TAB_NEXT, IDC_MOVE_TAB_PREVIOUS, IDC_SEARCH, IDC_DEBUG_FRAME_TOGGLE, IDC_WINDOW_MENU, IDC_MINIMIZE_WINDOW, IDC_MAXIMIZE_WINDOW, IDC_ALL_WINDOWS_FRONT, IDC_NAME_WINDOW, IDC_USE_SYSTEM_TITLE_BAR, IDC_RESTORE_WINDOW, IDC_OPEN_IN_PWA_WINDOW, IDC_MOVE_TAB_TO_NEW_WINDOW, IDC_COPY_URL, IDC_OPEN_IN_CHROME, IDC_SITE_SETTINGS, IDC_WEB_APP_MENU_APP_INFO, IDC_BOOKMARK_THIS_TAB, IDC_BOOKMARK_ALL_TABS, IDC_VIEW_SOURCE, IDC_PRINT, IDC_SAVE_PAGE, IDC_EMAIL_PAGE_LOCATION, IDC_BASIC_PRINT, IDC_SAVE_CREDIT_CARD_FOR_PAGE, IDC_TRANSLATE_PAGE, IDC_MANAGE_PASSWORDS_FOR_PAGE, IDC_ROUTE_MEDIA, IDC_WINDOW_MUTE_SITE, IDC_WINDOW_PIN_TAB, IDC_WINDOW_GROUP_TAB, IDC_MIGRATE_LOCAL_CREDIT_CARD_FOR_PAGE, IDC_SEND_TAB_TO_SELF, IDC_FOCUS_THIS_TAB, IDC_QRCODE_GENERATOR, IDC_WINDOW_CLOSE_TABS_TO_RIGHT, IDC_WINDOW_CLOSE_OTHER_TABS, IDC_NEW_TAB_TO_RIGHT, IDC_SAVE_AUTOFILL_ADDRESS, IDC_OFFERS_AND_REWARDS_FOR_PAGE, IDC_WEBAUTHN, IDC_SHARING_HUB, IDC_SHARING_HUB_MENU, IDC_VIRTUAL_CARD_MANUAL_FALLBACK, IDC_SHARING_HUB_SCREENSHOT, IDC_VIRTUAL_CARD_ENROLL, IDC_FOLLOW, IDC_UNFOLLOW, IDC_MUTE_TARGET_SITE, IDC_PIN_TARGET_TAB, IDC_GROUP_TARGET_TAB, IDC_DUPLICATE_TARGET_TAB, IDC_CUT, IDC_COPY, IDC_PASTE, IDC_EDIT_MENU, IDC_FIND, IDC_FIND_NEXT, IDC_FIND_PREVIOUS, IDC_CLOSE_FIND_OR_STOP, IDC_FIND_MENU, IDC_ZOOM_MENU, IDC_ZOOM_PLUS, IDC_ZOOM_NORMAL, IDC_ZOOM_MINUS, IDC_ZOOM_PERCENT_DISPLAY, IDC_FOCUS_TOOLBAR, IDC_FOCUS_LOCATION, IDC_FOCUS_SEARCH, IDC_FOCUS_MENU_BAR, IDC_FOCUS_NEXT_PANE, IDC_FOCUS_PREVIOUS_PANE, IDC_FOCUS_BOOKMARKS, IDC_FOCUS_INACTIVE_POPUP_FOR_ACCESSIBILITY, IDC_FOCUS_WEB_CONTENTS_PANE, IDC_OPEN_FILE, IDC_CREATE_SHORTCUT, IDC_DEVELOPER_MENU, IDC_DEV_TOOLS, IDC_DEV_TOOLS_CONSOLE, IDC_TASK_MANAGER, IDC_DEV_TOOLS_DEVICES, IDC_FEEDBACK, IDC_SHOW_BOOKMARK_BAR, IDC_SHOW_HISTORY, IDC_SHOW_BOOKMARK_MANAGER, IDC_SHOW_DOWNLOADS, IDC_CLEAR_BROWSING_DATA, IDC_IMPORT_SETTINGS, IDC_OPTIONS, IDC_EDIT_SEARCH_ENGINES, IDC_VIEW_PASSWORDS, IDC_ABOUT, IDC_HELP_PAGE_VIA_KEYBOARD, IDC_HELP_PAGE_VIA_MENU, IDC_SHOW_APP_MENU, IDC_MANAGE_EXTENSIONS, IDC_DEV_TOOLS_INSPECT, IDC_UPGRADE_DIALOG, IDC_PROFILING_ENABLED, IDC_BOOKMARKS_MENU, IDC_SHOW_SIGNIN, IDC_EXTENSION_ERRORS, IDC_SHOW_SETTINGS_CHANGE_FIRST, IDC_SHOW_SETTINGS_CHANGE_LAST, IDC_SHOW_AVATAR_MENU, IDC_EXTENSION_INSTALL_ERROR_FIRST, IDC_EXTENSION_INSTALL_ERROR_LAST, IDC_TOGGLE_REQUEST_TABLET_SITE, IDC_DEV_TOOLS_TOGGLE, IDC_RECENT_TABS_MENU, IDC_RECENT_TABS_NO_DEVICE_TABS, IDC_SHOW_SETTINGS_RESET_BUBBLE, IDC_SHOW_SYNC_ERROR, IDC_DISTILL_PAGE, IDC_HELP_MENU, IDC_SHOW_SRT_BUBBLE, IDC_ELEVATED_RECOVERY_DIALOG, IDC_TAKE_SCREENSHOT, IDC_MORE_TOOLS_MENU, IDC_TOGGLE_FULLSCREEN_TOOLBAR, IDC_CUSTOMIZE_TOUCH_BAR, IDC_SHOW_BETA_FORUM, IDC_TOGGLE_JAVASCRIPT_APPLE_EVENTS, IDC_INSTALL_PWA, IDC_SHOW_MANAGEMENT_PAGE, IDC_PASTE_AND_GO, IDC_SHOW_SAVE_LOCAL_CARD_SIGN_IN_PROMO_IF_APPLICABLE, IDC_CLOSE_SIGN_IN_PROMO, IDC_SHOW_FULL_URLS, IDC_CARET_BROWSING_TOGGLE, IDC_TOGGLE_QUICK_COMMANDS, IDC_CHROME_TIPS, IDC_CHROME_WHATS_NEW, IDC_PERFORMANCE, IDC_SPELLCHECK_SUGGESTION_0, IDC_SPELLCHECK_SUGGESTION_1, IDC_SPELLCHECK_SUGGESTION_2, IDC_SPELLCHECK_SUGGESTION_3, IDC_SPELLCHECK_SUGGESTION_4, IDC_SPELLCHECK_MENU, IDC_SPELLCHECK_LANGUAGES_FIRST, IDC_SPELLCHECK_LANGUAGES_LAST, IDC_CHECK_SPELLING_WHILE_TYPING, IDC_SPELLPANEL_TOGGLE, IDC_SPELLCHECK_ADD_TO_DICTIONARY, IDC_SPELLCHECK_MULTI_LINGUAL, IDC_WRITING_DIRECTION_MENU, IDC_WRITING_DIRECTION_DEFAULT, IDC_WRITING_DIRECTION_LTR, IDC_WRITING_DIRECTION_RTL, IDC_TRANSLATE_ORIGINAL_LANGUAGE_BASE, IDC_TRANSLATE_TARGET_LANGUAGE_BASE, IDC_CONTENT_CONTEXT_CUSTOM_FIRST, IDC_CONTENT_CONTEXT_CUSTOM_LAST, IDC_EXTENSIONS_CONTEXT_CUSTOM_FIRST, IDC_EXTENSIONS_CONTEXT_CUSTOM_LAST, IDC_CONTENT_CONTEXT_OPENLINKNEWTAB, IDC_CONTENT_CONTEXT_OPENLINKNEWWINDOW, IDC_CONTENT_CONTEXT_OPENLINKOFFTHERECORD, IDC_CONTENT_CONTEXT_SAVELINKAS, IDC_CONTENT_CONTEXT_COPYLINKLOCATION, IDC_CONTENT_CONTEXT_COPYEMAILADDRESS, IDC_CONTENT_CONTEXT_OPENLINKWITH, IDC_CONTENT_CONTEXT_COPYLINKTEXT, IDC_CONTENT_CONTEXT_OPENLINKINPROFILE, IDC_CONTENT_CONTEXT_OPENLINKBOOKMARKAPP, IDC_CONTENT_CONTEXT_SAVEIMAGEAS, IDC_CONTENT_CONTEXT_COPYIMAGELOCATION, IDC_CONTENT_CONTEXT_COPYIMAGE, IDC_CONTENT_CONTEXT_OPENIMAGENEWTAB, IDC_CONTENT_CONTEXT_SEARCHWEBFORIMAGE, IDC_CONTENT_CONTEXT_OPEN_ORIGINAL_IMAGE_NEW_TAB, IDC_CONTENT_CONTEXT_LOAD_IMAGE, IDC_CONTENT_CONTEXT_SEARCHLENSFORIMAGE, IDC_CONTENT_CONTEXT_SAVEAVAS, IDC_CONTENT_CONTEXT_COPYAVLOCATION, IDC_CONTENT_CONTEXT_OPENAVNEWTAB, IDC_CONTENT_CONTEXT_PICTUREINPICTURE, IDC_CONTENT_CONTEXT_PLAYPAUSE, IDC_CONTENT_CONTEXT_MUTE, IDC_CONTENT_CONTEXT_LOOP, IDC_CONTENT_CONTEXT_CONTROLS, IDC_CONTENT_CONTEXT_ROTATECW, IDC_CONTENT_CONTEXT_ROTATECCW, IDC_CONTENT_CONTEXT_COPY, IDC_CONTENT_CONTEXT_CUT, IDC_CONTENT_CONTEXT_PASTE, IDC_CONTENT_CONTEXT_DELETE, IDC_CONTENT_CONTEXT_UNDO, IDC_CONTENT_CONTEXT_REDO, IDC_CONTENT_CONTEXT_SELECTALL, IDC_CONTENT_CONTEXT_PASTE_AND_MATCH_STYLE, IDC_CONTENT_CONTEXT_COPYLINKTOTEXT, IDC_CONTENT_CONTEXT_RESHARELINKTOTEXT, IDC_CONTENT_CONTEXT_REMOVELINKTOTEXT, IDC_CONTENT_CONTEXT_TRANSLATE, IDC_CONTENT_CONTEXT_INSPECTELEMENT, IDC_CONTENT_CONTEXT_VIEWPAGEINFO, IDC_CONTENT_CONTEXT_LANGUAGE_SETTINGS, IDC_CONTENT_CONTEXT_LOOK_UP, IDC_CONTENT_CONTEXT_NO_SPELLING_SUGGESTIONS, IDC_CONTENT_CONTEXT_SPELLING_SUGGESTION, IDC_CONTENT_CONTEXT_SPELLING_TOGGLE, IDC_CONTENT_CONTEXT_OPEN_IN_READ_ANYTHING, IDC_CONTENT_CONTEXT_RUN_PDF_OCR, IDC_CONTENT_CONTEXT_INSPECTBACKGROUNDPAGE, IDC_CONTENT_CONTEXT_RELOAD_PACKAGED_APP, IDC_CONTENT_CONTEXT_RESTART_PACKAGED_APP, IDC_CONTENT_CONTEXT_LENS_REGION_SEARCH, IDC_CONTENT_CONTEXT_WEB_REGION_SEARCH, IDC_CONTENT_CONTEXT_GENERATEPASSWORD, IDC_CONTENT_CONTEXT_EXIT_FULLSCREEN, IDC_CONTENT_CONTEXT_SHOWALLSAVEDPASSWORDS, IDC_CONTENT_CONTEXT_PARTIAL_TRANSLATE, IDC_CONTENT_CONTEXT_RELOADFRAME, IDC_CONTENT_CONTEXT_VIEWFRAMESOURCE, IDC_CONTENT_CONTEXT_VIEWFRAMEINFO, IDC_CONTENT_CONTEXT_ADD_A_NOTE, IDC_CONTENT_CONTEXT_GOTOURL, IDC_CONTENT_CONTEXT_SEARCHWEBFOR, IDC_CONTENT_CONTEXT_OPEN_WITH1, IDC_CONTENT_CONTEXT_OPEN_WITH2, IDC_CONTENT_CONTEXT_OPEN_WITH3, IDC_CONTENT_CONTEXT_OPEN_WITH4, IDC_CONTENT_CONTEXT_OPEN_WITH5, IDC_CONTENT_CONTEXT_OPEN_WITH6, IDC_CONTENT_CONTEXT_OPEN_WITH7, IDC_CONTENT_CONTEXT_OPEN_WITH8, IDC_CONTENT_CONTEXT_OPEN_WITH9, IDC_CONTENT_CONTEXT_OPEN_WITH10, IDC_CONTENT_CONTEXT_OPEN_WITH11, IDC_CONTENT_CONTEXT_OPEN_WITH12, IDC_CONTENT_CONTEXT_OPEN_WITH13, IDC_CONTENT_CONTEXT_OPEN_WITH14, IDC_CONTENT_CONTEXT_EMOJI, IDC_BOOKMARK_BAR_OPEN_ALL, IDC_BOOKMARK_BAR_OPEN_ALL_NEW_WINDOW, IDC_BOOKMARK_BAR_OPEN_ALL_INCOGNITO, IDC_BOOKMARK_BAR_OPEN_INCOGNITO, IDC_BOOKMARK_BAR_OPEN_ALL_NEW_TAB_GROUP, IDC_BOOKMARK_BAR_RENAME_FOLDER, IDC_BOOKMARK_BAR_EDIT, IDC_BOOKMARK_BAR_REMOVE, IDC_BOOKMARK_BAR_UNDO, IDC_BOOKMARK_BAR_REDO, IDC_BOOKMARK_BAR_ADD_NEW_BOOKMARK, IDC_BOOKMARK_BAR_NEW_FOLDER, IDC_BOOKMARK_MANAGER, IDC_BOOKMARK_BAR_ALWAYS_SHOW, IDC_BOOKMARK_BAR_SHOW_APPS_SHORTCUT, IDC_BOOKMARK_BAR_SHOW_READING_LIST, IDC_BOOKMARK_BAR_SHOW_MANAGED_BOOKMARKS, IDC_BOOKMARK_BAR_TRACK_PRICE_FOR_SHOPPING_BOOKMARK, IDC_BOOKMARK_BAR_UNTRACK_PRICE_FOR_SHOPPING_BOOKMARK, IDC_CONTENT_CONTEXT_SHARING_CLICK_TO_CALL_SINGLE_DEVICE, IDC_CONTENT_CONTEXT_SHARING_CLICK_TO_CALL_MULTIPLE_DEVICES, IDC_CONTENT_CONTEXT_SHARING_SHARED_CLIPBOARD_SINGLE_DEVICE, IDC_CONTENT_CONTEXT_SHARING_SHARED_CLIPBOARD_MULTIPLE_DEVICES, IDC_CONTENT_CONTEXT_GENERATE_QR_CODE, IDC_CONTENT_CONTEXT_SHARING_SUBMENU, IDC_CONTENT_CLIPBOARD_HISTORY_MENU, IDC_STATUS_TRAY_KEEP_CHROME_RUNNING_IN_BACKGROUND, IDC_MEDIA_ROUTER_ABOUT, IDC_MEDIA_ROUTER_HELP, IDC_MEDIA_ROUTER_LEARN_MORE, IDC_MEDIA_ROUTER_ALWAYS_SHOW_TOOLBAR_ACTION, IDC_MEDIA_ROUTER_SHOWN_BY_POLICY, IDC_MEDIA_ROUTER_SHOW_IN_TOOLBAR, IDC_MEDIA_ROUTER_TOGGLE_MEDIA_REMOTING, IDC_MEDIA_TOOLBAR_CONTEXT_SHOW_OTHER_SESSIONS, IDC_MEDIA_STREAM_DEVICE_STATUS_TRAY, IDC_MEDIA_CONTEXT_MEDIA_STREAM_CAPTURE_LIST_FIRST, IDC_MEDIA_CONTEXT_MEDIA_STREAM_CAPTURE_LIST_LAST, IDC_MEDIA_STREAM_DEVICE_ALWAYS_ALLOW, IDC_CONTENT_CONTEXT_PROTOCOL_HANDLER_FIRST, IDC_CONTENT_CONTEXT_PROTOCOL_HANDLER_LAST, IDC_CONTENT_CONTEXT_PROTOCOL_HANDLER_SETTINGS, IDC_OPEN_LINK_IN_PROFILE_FIRST, IDC_OPEN_LINK_IN_PROFILE_LAST, IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION1, IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION2, IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION3, IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION4, IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION5, IDC_CONTENT_CONTEXT_ACCESSIBILITY_LABELS_TOGGLE, IDC_CONTENT_CONTEXT_ACCESSIBILITY_LABELS, IDC_CONTENT_CONTEXT_ACCESSIBILITY_LABELS_TOGGLE_ONCE, IDC_RUN_SCREEN_AI_VISUAL_ANNOTATIONS, IDC_TAB_SEARCH, IDC_TAB_SEARCH_CLOSE, IDC_DEBUG_TOGGLE_TABLET_MODE, IDC_DEBUG_PRINT_VIEW_TREE, IDC_DEBUG_PRINT_VIEW_TREE_DETAILS, IDC_CONTENT_CONTEXT_AUTOFILL_CUSTOM_FIRST, IDC_CONTENT_CONTEXT_AUTOFILL_CUSTOM_LAST, IDC_LIVE_CAPTION, IDC_SHOW_BRAVE_REWARDS, IDC_NEW_TOR_CONNECTION_FOR_SITE, IDC_NEW_OFFTHERECORD_WINDOW_TOR, IDC_CONTENT_CONTEXT_OPENLINKTOR, IDC_SHOW_BRAVE_SYNC, IDC_SHOW_BRAVE_WALLET, IDC_ADD_NEW_PROFILE, IDC_OPEN_GUEST_PROFILE, IDC_SHOW_BRAVE_WEBCOMPAT_REPORTER, IDC_SPEEDREADER_ICON_ONCLICK, IDC_SIDEBAR_SHOW_OPTION_MENU, IDC_SIDEBAR_SHOW_OPTION_ALWAYS, IDC_SIDEBAR_SHOW_OPTION_MOUSEOVER, IDC_SIDEBAR_SHOW_OPTION_NEVER, IDC_CONTENT_CONTEXT_IMPORT_IPFS, IDC_CONTENT_CONTEXT_IMPORT_LINK_IPFS, IDC_CONTENT_CONTEXT_IMPORT_IPFS_PAGE, IDC_CONTENT_CONTEXT_IMPORT_IMAGE_IPFS, IDC_CONTENT_CONTEXT_IMPORT_AUDIO_IPFS, IDC_CONTENT_CONTEXT_IMPORT_VIDEO_IPFS, IDC_CONTENT_CONTEXT_IMPORT_SELECTED_TEXT_IPFS, IDC_APP_MENU_IPFS, IDC_APP_MENU_IPFS_PUBLISH_LOCAL_FILE, IDC_APP_MENU_IPFS_PUBLISH_LOCAL_FOLDER, IDC_SHOW_BRAVE_WALLET_PANEL, IDC_CLOSE_BRAVE_WALLET_PANEL, IDC_SHOW_BRAVE_VPN_PANEL, IDC_BRAVE_VPN_MENU, IDC_TOGGLE_BRAVE_VPN_TOOLBAR_BUTTON, IDC_SEND_BRAVE_VPN_FEEDBACK, IDC_ABOUT_BRAVE_VPN, IDC_MANAGE_BRAVE_VPN_PLAN, IDC_TOGGLE_BRAVE_VPN, IDC_APP_MENU_IPFS_SHARE_LOCAL_FILE, IDC_APP_MENU_IPFS_SHARE_LOCAL_FOLDER, IDC_APP_MENU_IPFS_OPEN_FILES, IDC_APP_MENU_IPFS_UPDATE_IPNS, IDC_CONTENT_CONTEXT_FORCE_PASTE, IDC_COPY_CLEAN_LINK, IDC_TOGGLE_TAB_MUTE, IDC_SIDEBAR_TOGGLE_POSITION, IDC_CONTENT_CONTEXT_COPY_TEXT_FROM_IMAGE, IDC_CONTENT_CONTEXT_IMPORT_IPNS_KEYS_START, IDC_CONTENT_CONTEXT_IMPORT_IPNS_KEYS_END, IDC_BRAVE_BOOKMARK_BAR_SUBMENU, IDC_BRAVE_BOOKMARK_BAR_ALWAYS, IDC_BRAVE_BOOKMARK_BAR_NTP, IDC_BRAVE_BOOKMARK_BAR_NEVER, IDC_BRAVE_COMMANDS_LAST};
}

std::string GetCommandName(int command_id) {
  switch (command_id) {
    case IDC_BACK:
      return "Back";
    case IDC_FORWARD:
      return "Forward";
    case IDC_RELOAD:
      return "Reload";
    case IDC_HOME:
      return "Home";
    case IDC_OPEN_CURRENT_URL:
      return "Open Current Url";
    case IDC_STOP:
      return "Stop";
    case IDC_RELOAD_BYPASSING_CACHE:
      return "Reload Bypassing Cache";
    case IDC_RELOAD_CLEARING_CACHE:
      return "Reload Clearing Cache";
    case IDC_NEW_WINDOW:
      return "New Window";
    case IDC_NEW_INCOGNITO_WINDOW:
      return "New Incognito Window";
    case IDC_PIN_TO_START_SCREEN:
      return "Pin To Start Screen";
    case IDC_CLOSE_WINDOW:
      return "Close Window";
    case IDC_ALWAYS_ON_TOP:
      return "Always On Top";
    case IDC_NEW_TAB:
      return "New Tab";
    case IDC_CLOSE_TAB:
      return "Close Tab";
    case IDC_SELECT_NEXT_TAB:
      return "Select Next Tab";
    case IDC_SELECT_PREVIOUS_TAB:
      return "Select Previous Tab";
    case IDC_SELECT_TAB_0:
      return "Select Tab 0";
    case IDC_SELECT_TAB_1:
      return "Select Tab 1";
    case IDC_SELECT_TAB_2:
      return "Select Tab 2";
    case IDC_SELECT_TAB_3:
      return "Select Tab 3";
    case IDC_SELECT_TAB_4:
      return "Select Tab 4";
    case IDC_SELECT_TAB_5:
      return "Select Tab 5";
    case IDC_SELECT_TAB_6:
      return "Select Tab 6";
    case IDC_SELECT_TAB_7:
      return "Select Tab 7";
    case IDC_SELECT_LAST_TAB:
      return "Select Last Tab";
    case IDC_DUPLICATE_TAB:
      return "Duplicate Tab";
    case IDC_RESTORE_TAB:
      return "Restore Tab";
    case IDC_SHOW_AS_TAB:
      return "Show As Tab";
    case IDC_FULLSCREEN:
      return "Fullscreen";
    case IDC_EXIT:
      return "Exit";
    case IDC_MOVE_TAB_NEXT:
      return "Move Tab Next";
    case IDC_MOVE_TAB_PREVIOUS:
      return "Move Tab Previous";
    case IDC_SEARCH:
      return "Search";
    case IDC_DEBUG_FRAME_TOGGLE:
      return "Debug Frame Toggle";
    case IDC_WINDOW_MENU:
      return "Window Menu";
    case IDC_MINIMIZE_WINDOW:
      return "Minimize Window";
    case IDC_MAXIMIZE_WINDOW:
      return "Maximize Window";
    case IDC_ALL_WINDOWS_FRONT:
      return "All Windows Front";
    case IDC_NAME_WINDOW:
      return "Name Window";
    case IDC_USE_SYSTEM_TITLE_BAR:
      return "Use System Title Bar";
    case IDC_RESTORE_WINDOW:
      return "Restore Window";
    case IDC_OPEN_IN_PWA_WINDOW:
      return "Open In Pwa Window";
    case IDC_MOVE_TAB_TO_NEW_WINDOW:
      return "Move Tab To New Window";
    case IDC_COPY_URL:
      return "Copy Url";
    case IDC_OPEN_IN_CHROME:
      return "Open In Chrome";
    case IDC_SITE_SETTINGS:
      return "Site Settings";
    case IDC_WEB_APP_MENU_APP_INFO:
      return "Web App Menu App Info";
    case IDC_BOOKMARK_THIS_TAB:
      return "Bookmark This Tab";
    case IDC_BOOKMARK_ALL_TABS:
      return "Bookmark All Tabs";
    case IDC_VIEW_SOURCE:
      return "View Source";
    case IDC_PRINT:
      return "Print";
    case IDC_SAVE_PAGE:
      return "Save Page";
    case IDC_EMAIL_PAGE_LOCATION:
      return "Email Page Location";
    case IDC_BASIC_PRINT:
      return "Basic Print";
    case IDC_SAVE_CREDIT_CARD_FOR_PAGE:
      return "Save Credit Card For Page";
    case IDC_TRANSLATE_PAGE:
      return "Translate Page";
    case IDC_MANAGE_PASSWORDS_FOR_PAGE:
      return "Manage Passwords For Page";
    case IDC_ROUTE_MEDIA:
      return "Route Media";
    case IDC_WINDOW_MUTE_SITE:
      return "Window Mute Site";
    case IDC_WINDOW_PIN_TAB:
      return "Window Pin Tab";
    case IDC_WINDOW_GROUP_TAB:
      return "Window Group Tab";
    case IDC_MIGRATE_LOCAL_CREDIT_CARD_FOR_PAGE:
      return "Migrate Local Credit Card For Page";
    case IDC_SEND_TAB_TO_SELF:
      return "Send Tab To Self";
    case IDC_FOCUS_THIS_TAB:
      return "Focus This Tab";
    case IDC_QRCODE_GENERATOR:
      return "Qrcode Generator";
    case IDC_WINDOW_CLOSE_TABS_TO_RIGHT:
      return "Window Close Tabs To Right";
    case IDC_WINDOW_CLOSE_OTHER_TABS:
      return "Window Close Other Tabs";
    case IDC_NEW_TAB_TO_RIGHT:
      return "New Tab To Right";
    case IDC_SAVE_AUTOFILL_ADDRESS:
      return "Save Autofill Address";
    case IDC_OFFERS_AND_REWARDS_FOR_PAGE:
      return "Offers And Rewards For Page";
    case IDC_WEBAUTHN:
      return "Webauthn";
    case IDC_SHARING_HUB:
      return "Sharing Hub";
    case IDC_SHARING_HUB_MENU:
      return "Sharing Hub Menu";
    case IDC_VIRTUAL_CARD_MANUAL_FALLBACK:
      return "Virtual Card Manual Fallback";
    case IDC_SHARING_HUB_SCREENSHOT:
      return "Sharing Hub Screenshot";
    case IDC_VIRTUAL_CARD_ENROLL:
      return "Virtual Card Enroll";
    case IDC_FOLLOW:
      return "Follow";
    case IDC_UNFOLLOW:
      return "Unfollow";
    case IDC_MUTE_TARGET_SITE:
      return "Mute Target Site";
    case IDC_PIN_TARGET_TAB:
      return "Pin Target Tab";
    case IDC_GROUP_TARGET_TAB:
      return "Group Target Tab";
    case IDC_DUPLICATE_TARGET_TAB:
      return "Duplicate Target Tab";
    case IDC_CUT:
      return "Cut";
    case IDC_COPY:
      return "Copy";
    case IDC_PASTE:
      return "Paste";
    case IDC_EDIT_MENU:
      return "Edit Menu";
    case IDC_FIND:
      return "Find";
    case IDC_FIND_NEXT:
      return "Find Next";
    case IDC_FIND_PREVIOUS:
      return "Find Previous";
    case IDC_CLOSE_FIND_OR_STOP:
      return "Close Find Or Stop";
    case IDC_FIND_MENU:
      return "Find Menu";
    case IDC_ZOOM_MENU:
      return "Zoom Menu";
    case IDC_ZOOM_PLUS:
      return "Zoom Plus";
    case IDC_ZOOM_NORMAL:
      return "Zoom Normal";
    case IDC_ZOOM_MINUS:
      return "Zoom Minus";
    case IDC_ZOOM_PERCENT_DISPLAY:
      return "Zoom Percent Display";
    case IDC_FOCUS_TOOLBAR:
      return "Focus Toolbar";
    case IDC_FOCUS_LOCATION:
      return "Focus Location";
    case IDC_FOCUS_SEARCH:
      return "Focus Search";
    case IDC_FOCUS_MENU_BAR:
      return "Focus Menu Bar";
    case IDC_FOCUS_NEXT_PANE:
      return "Focus Next Pane";
    case IDC_FOCUS_PREVIOUS_PANE:
      return "Focus Previous Pane";
    case IDC_FOCUS_BOOKMARKS:
      return "Focus Bookmarks";
    case IDC_FOCUS_INACTIVE_POPUP_FOR_ACCESSIBILITY:
      return "Focus Inactive Popup For Accessibility";
    case IDC_FOCUS_WEB_CONTENTS_PANE:
      return "Focus Web Contents Pane";
    case IDC_OPEN_FILE:
      return "Open File";
    case IDC_CREATE_SHORTCUT:
      return "Create Shortcut";
    case IDC_DEVELOPER_MENU:
      return "Developer Menu";
    case IDC_DEV_TOOLS:
      return "Dev Tools";
    case IDC_DEV_TOOLS_CONSOLE:
      return "Dev Tools Console";
    case IDC_TASK_MANAGER:
      return "Task Manager";
    case IDC_DEV_TOOLS_DEVICES:
      return "Dev Tools Devices";
    case IDC_FEEDBACK:
      return "Feedback";
    case IDC_SHOW_BOOKMARK_BAR:
      return "Show Bookmark Bar";
    case IDC_SHOW_HISTORY:
      return "Show History";
    case IDC_SHOW_BOOKMARK_MANAGER:
      return "Show Bookmark Manager";
    case IDC_SHOW_DOWNLOADS:
      return "Show Downloads";
    case IDC_CLEAR_BROWSING_DATA:
      return "Clear Browsing Data";
    case IDC_IMPORT_SETTINGS:
      return "Import Settings";
    case IDC_OPTIONS:
      return "Options";
    case IDC_EDIT_SEARCH_ENGINES:
      return "Edit Search Engines";
    case IDC_VIEW_PASSWORDS:
      return "View Passwords";
    case IDC_ABOUT:
      return "About";
    case IDC_HELP_PAGE_VIA_KEYBOARD:
      return "Help Page Via Keyboard";
    case IDC_HELP_PAGE_VIA_MENU:
      return "Help Page Via Menu";
    case IDC_SHOW_APP_MENU:
      return "Show App Menu";
    case IDC_MANAGE_EXTENSIONS:
      return "Manage Extensions";
    case IDC_DEV_TOOLS_INSPECT:
      return "Dev Tools Inspect";
    case IDC_UPGRADE_DIALOG:
      return "Upgrade Dialog";
    case IDC_PROFILING_ENABLED:
      return "Profiling Enabled";
    case IDC_BOOKMARKS_MENU:
      return "Bookmarks Menu";
    case IDC_SHOW_SIGNIN:
      return "Show Signin";
    case IDC_EXTENSION_ERRORS:
      return "Extension Errors";
    case IDC_SHOW_SETTINGS_CHANGE_FIRST:
      return "Show Settings Change First";
    case IDC_SHOW_SETTINGS_CHANGE_LAST:
      return "Show Settings Change Last";
    case IDC_SHOW_AVATAR_MENU:
      return "Show Avatar Menu";
    case IDC_EXTENSION_INSTALL_ERROR_FIRST:
      return "Extension Install Error First";
    case IDC_EXTENSION_INSTALL_ERROR_LAST:
      return "Extension Install Error Last";
    case IDC_TOGGLE_REQUEST_TABLET_SITE:
      return "Toggle Request Tablet Site";
    case IDC_DEV_TOOLS_TOGGLE:
      return "Dev Tools Toggle";
    case IDC_RECENT_TABS_MENU:
      return "Recent Tabs Menu";
    case IDC_RECENT_TABS_NO_DEVICE_TABS:
      return "Recent Tabs No Device Tabs";
    case IDC_SHOW_SETTINGS_RESET_BUBBLE:
      return "Show Settings Reset Bubble";
    case IDC_SHOW_SYNC_ERROR:
      return "Show Sync Error";
    case IDC_DISTILL_PAGE:
      return "Distill Page";
    case IDC_HELP_MENU:
      return "Help Menu";
    case IDC_SHOW_SRT_BUBBLE:
      return "Show Srt Bubble";
    case IDC_ELEVATED_RECOVERY_DIALOG:
      return "Elevated Recovery Dialog";
    case IDC_TAKE_SCREENSHOT:
      return "Take Screenshot";
    case IDC_MORE_TOOLS_MENU:
      return "More Tools Menu";
    case IDC_TOGGLE_FULLSCREEN_TOOLBAR:
      return "Toggle Fullscreen Toolbar";
    case IDC_CUSTOMIZE_TOUCH_BAR:
      return "Customize Touch Bar";
    case IDC_SHOW_BETA_FORUM:
      return "Show Beta Forum";
    case IDC_TOGGLE_JAVASCRIPT_APPLE_EVENTS:
      return "Toggle Javascript Apple Events";
    case IDC_INSTALL_PWA:
      return "Install Pwa";
    case IDC_SHOW_MANAGEMENT_PAGE:
      return "Show Management Page";
    case IDC_PASTE_AND_GO:
      return "Paste And Go";
    case IDC_SHOW_SAVE_LOCAL_CARD_SIGN_IN_PROMO_IF_APPLICABLE:
      return "Show Save Local Card Sign In Promo If Applicable";
    case IDC_CLOSE_SIGN_IN_PROMO:
      return "Close Sign In Promo";
    case IDC_SHOW_FULL_URLS:
      return "Show Full Urls";
    case IDC_CARET_BROWSING_TOGGLE:
      return "Caret Browsing Toggle";
    case IDC_TOGGLE_QUICK_COMMANDS:
      return "Toggle Quick Commands";
    case IDC_CHROME_TIPS:
      return "Chrome Tips";
    case IDC_CHROME_WHATS_NEW:
      return "Chrome Whats New";
    case IDC_PERFORMANCE:
      return "Performance";
    case IDC_SPELLCHECK_SUGGESTION_0:
      return "Spellcheck Suggestion 0";
    case IDC_SPELLCHECK_SUGGESTION_1:
      return "Spellcheck Suggestion 1";
    case IDC_SPELLCHECK_SUGGESTION_2:
      return "Spellcheck Suggestion 2";
    case IDC_SPELLCHECK_SUGGESTION_3:
      return "Spellcheck Suggestion 3";
    case IDC_SPELLCHECK_SUGGESTION_4:
      return "Spellcheck Suggestion 4";
    case IDC_SPELLCHECK_MENU:
      return "Spellcheck Menu";
    case IDC_SPELLCHECK_LANGUAGES_FIRST:
      return "Spellcheck Languages First";
    case IDC_SPELLCHECK_LANGUAGES_LAST:
      return "Spellcheck Languages Last";
    case IDC_CHECK_SPELLING_WHILE_TYPING:
      return "Check Spelling While Typing";
    case IDC_SPELLPANEL_TOGGLE:
      return "Spellpanel Toggle";
    case IDC_SPELLCHECK_ADD_TO_DICTIONARY:
      return "Spellcheck Add To Dictionary";
    case IDC_SPELLCHECK_MULTI_LINGUAL:
      return "Spellcheck Multi Lingual";
    case IDC_WRITING_DIRECTION_MENU:
      return "Writing Direction Menu";
    case IDC_WRITING_DIRECTION_DEFAULT:
      return "Writing Direction Default";
    case IDC_WRITING_DIRECTION_LTR:
      return "Writing Direction Ltr";
    case IDC_WRITING_DIRECTION_RTL:
      return "Writing Direction Rtl";
    case IDC_TRANSLATE_ORIGINAL_LANGUAGE_BASE:
      return "Translate Original Language Base";
    case IDC_TRANSLATE_TARGET_LANGUAGE_BASE:
      return "Translate Target Language Base";
    case IDC_CONTENT_CONTEXT_CUSTOM_FIRST:
      return "Content Context Custom First";
    case IDC_CONTENT_CONTEXT_CUSTOM_LAST:
      return "Content Context Custom Last";
    case IDC_EXTENSIONS_CONTEXT_CUSTOM_FIRST:
      return "Extensions Context Custom First";
    case IDC_EXTENSIONS_CONTEXT_CUSTOM_LAST:
      return "Extensions Context Custom Last";
    case IDC_CONTENT_CONTEXT_OPENLINKNEWTAB:
      return "Content Context Openlinknewtab";
    case IDC_CONTENT_CONTEXT_OPENLINKNEWWINDOW:
      return "Content Context Openlinknewwindow";
    case IDC_CONTENT_CONTEXT_OPENLINKOFFTHERECORD:
      return "Content Context Openlinkofftherecord";
    case IDC_CONTENT_CONTEXT_SAVELINKAS:
      return "Content Context Savelinkas";
    case IDC_CONTENT_CONTEXT_COPYLINKLOCATION:
      return "Content Context Copylinklocation";
    case IDC_CONTENT_CONTEXT_COPYEMAILADDRESS:
      return "Content Context Copyemailaddress";
    case IDC_CONTENT_CONTEXT_OPENLINKWITH:
      return "Content Context Openlinkwith";
    case IDC_CONTENT_CONTEXT_COPYLINKTEXT:
      return "Content Context Copylinktext";
    case IDC_CONTENT_CONTEXT_OPENLINKINPROFILE:
      return "Content Context Openlinkinprofile";
    case IDC_CONTENT_CONTEXT_OPENLINKBOOKMARKAPP:
      return "Content Context Openlinkbookmarkapp";
    case IDC_CONTENT_CONTEXT_SAVEIMAGEAS:
      return "Content Context Saveimageas";
    case IDC_CONTENT_CONTEXT_COPYIMAGELOCATION:
      return "Content Context Copyimagelocation";
    case IDC_CONTENT_CONTEXT_COPYIMAGE:
      return "Content Context Copyimage";
    case IDC_CONTENT_CONTEXT_OPENIMAGENEWTAB:
      return "Content Context Openimagenewtab";
    case IDC_CONTENT_CONTEXT_SEARCHWEBFORIMAGE:
      return "Content Context Searchwebforimage";
    case IDC_CONTENT_CONTEXT_OPEN_ORIGINAL_IMAGE_NEW_TAB:
      return "Content Context Open Original Image New Tab";
    case IDC_CONTENT_CONTEXT_LOAD_IMAGE:
      return "Content Context Load Image";
    case IDC_CONTENT_CONTEXT_SEARCHLENSFORIMAGE:
      return "Content Context Searchlensforimage";
    case IDC_CONTENT_CONTEXT_SAVEAVAS:
      return "Content Context Saveavas";
    case IDC_CONTENT_CONTEXT_COPYAVLOCATION:
      return "Content Context Copyavlocation";
    case IDC_CONTENT_CONTEXT_OPENAVNEWTAB:
      return "Content Context Openavnewtab";
    case IDC_CONTENT_CONTEXT_PICTUREINPICTURE:
      return "Content Context Pictureinpicture";
    case IDC_CONTENT_CONTEXT_PLAYPAUSE:
      return "Content Context Playpause";
    case IDC_CONTENT_CONTEXT_MUTE:
      return "Content Context Mute";
    case IDC_CONTENT_CONTEXT_LOOP:
      return "Content Context Loop";
    case IDC_CONTENT_CONTEXT_CONTROLS:
      return "Content Context Controls";
    case IDC_CONTENT_CONTEXT_ROTATECW:
      return "Content Context Rotatecw";
    case IDC_CONTENT_CONTEXT_ROTATECCW:
      return "Content Context Rotateccw";
    case IDC_CONTENT_CONTEXT_COPY:
      return "Content Context Copy";
    case IDC_CONTENT_CONTEXT_CUT:
      return "Content Context Cut";
    case IDC_CONTENT_CONTEXT_PASTE:
      return "Content Context Paste";
    case IDC_CONTENT_CONTEXT_DELETE:
      return "Content Context Delete";
    case IDC_CONTENT_CONTEXT_UNDO:
      return "Content Context Undo";
    case IDC_CONTENT_CONTEXT_REDO:
      return "Content Context Redo";
    case IDC_CONTENT_CONTEXT_SELECTALL:
      return "Content Context Selectall";
    case IDC_CONTENT_CONTEXT_PASTE_AND_MATCH_STYLE:
      return "Content Context Paste And Match Style";
    case IDC_CONTENT_CONTEXT_COPYLINKTOTEXT:
      return "Content Context Copylinktotext";
    case IDC_CONTENT_CONTEXT_RESHARELINKTOTEXT:
      return "Content Context Resharelinktotext";
    case IDC_CONTENT_CONTEXT_REMOVELINKTOTEXT:
      return "Content Context Removelinktotext";
    case IDC_CONTENT_CONTEXT_TRANSLATE:
      return "Content Context Translate";
    case IDC_CONTENT_CONTEXT_INSPECTELEMENT:
      return "Content Context Inspectelement";
    case IDC_CONTENT_CONTEXT_VIEWPAGEINFO:
      return "Content Context Viewpageinfo";
    case IDC_CONTENT_CONTEXT_LANGUAGE_SETTINGS:
      return "Content Context Language Settings";
    case IDC_CONTENT_CONTEXT_LOOK_UP:
      return "Content Context Look Up";
    case IDC_CONTENT_CONTEXT_NO_SPELLING_SUGGESTIONS:
      return "Content Context No Spelling Suggestions";
    case IDC_CONTENT_CONTEXT_SPELLING_SUGGESTION:
      return "Content Context Spelling Suggestion";
    case IDC_CONTENT_CONTEXT_SPELLING_TOGGLE:
      return "Content Context Spelling Toggle";
    case IDC_CONTENT_CONTEXT_OPEN_IN_READ_ANYTHING:
      return "Content Context Open In Read Anything";
    case IDC_CONTENT_CONTEXT_RUN_PDF_OCR:
      return "Content Context Run Pdf Ocr";
    case IDC_CONTENT_CONTEXT_INSPECTBACKGROUNDPAGE:
      return "Content Context Inspectbackgroundpage";
    case IDC_CONTENT_CONTEXT_RELOAD_PACKAGED_APP:
      return "Content Context Reload Packaged App";
    case IDC_CONTENT_CONTEXT_RESTART_PACKAGED_APP:
      return "Content Context Restart Packaged App";
    case IDC_CONTENT_CONTEXT_LENS_REGION_SEARCH:
      return "Content Context Lens Region Search";
    case IDC_CONTENT_CONTEXT_WEB_REGION_SEARCH:
      return "Content Context Web Region Search";
    case IDC_CONTENT_CONTEXT_GENERATEPASSWORD:
      return "Content Context Generatepassword";
    case IDC_CONTENT_CONTEXT_EXIT_FULLSCREEN:
      return "Content Context Exit Fullscreen";
    case IDC_CONTENT_CONTEXT_SHOWALLSAVEDPASSWORDS:
      return "Content Context Showallsavedpasswords";
    case IDC_CONTENT_CONTEXT_PARTIAL_TRANSLATE:
      return "Content Context Partial Translate";
    case IDC_CONTENT_CONTEXT_RELOADFRAME:
      return "Content Context Reloadframe";
    case IDC_CONTENT_CONTEXT_VIEWFRAMESOURCE:
      return "Content Context Viewframesource";
    case IDC_CONTENT_CONTEXT_VIEWFRAMEINFO:
      return "Content Context Viewframeinfo";
    case IDC_CONTENT_CONTEXT_ADD_A_NOTE:
      return "Content Context Add A Note";
    case IDC_CONTENT_CONTEXT_GOTOURL:
      return "Content Context Gotourl";
    case IDC_CONTENT_CONTEXT_SEARCHWEBFOR:
      return "Content Context Searchwebfor";
    case IDC_CONTENT_CONTEXT_OPEN_WITH1:
      return "Content Context Open With1";
    case IDC_CONTENT_CONTEXT_OPEN_WITH2:
      return "Content Context Open With2";
    case IDC_CONTENT_CONTEXT_OPEN_WITH3:
      return "Content Context Open With3";
    case IDC_CONTENT_CONTEXT_OPEN_WITH4:
      return "Content Context Open With4";
    case IDC_CONTENT_CONTEXT_OPEN_WITH5:
      return "Content Context Open With5";
    case IDC_CONTENT_CONTEXT_OPEN_WITH6:
      return "Content Context Open With6";
    case IDC_CONTENT_CONTEXT_OPEN_WITH7:
      return "Content Context Open With7";
    case IDC_CONTENT_CONTEXT_OPEN_WITH8:
      return "Content Context Open With8";
    case IDC_CONTENT_CONTEXT_OPEN_WITH9:
      return "Content Context Open With9";
    case IDC_CONTENT_CONTEXT_OPEN_WITH10:
      return "Content Context Open With10";
    case IDC_CONTENT_CONTEXT_OPEN_WITH11:
      return "Content Context Open With11";
    case IDC_CONTENT_CONTEXT_OPEN_WITH12:
      return "Content Context Open With12";
    case IDC_CONTENT_CONTEXT_OPEN_WITH13:
      return "Content Context Open With13";
    case IDC_CONTENT_CONTEXT_OPEN_WITH14:
      return "Content Context Open With14";
    case IDC_CONTENT_CONTEXT_EMOJI:
      return "Content Context Emoji";
    case IDC_BOOKMARK_BAR_OPEN_ALL:
      return "Bookmark Bar Open All";
    case IDC_BOOKMARK_BAR_OPEN_ALL_NEW_WINDOW:
      return "Bookmark Bar Open All New Window";
    case IDC_BOOKMARK_BAR_OPEN_ALL_INCOGNITO:
      return "Bookmark Bar Open All Incognito";
    case IDC_BOOKMARK_BAR_OPEN_INCOGNITO:
      return "Bookmark Bar Open Incognito";
    case IDC_BOOKMARK_BAR_OPEN_ALL_NEW_TAB_GROUP:
      return "Bookmark Bar Open All New Tab Group";
    case IDC_BOOKMARK_BAR_RENAME_FOLDER:
      return "Bookmark Bar Rename Folder";
    case IDC_BOOKMARK_BAR_EDIT:
      return "Bookmark Bar Edit";
    case IDC_BOOKMARK_BAR_REMOVE:
      return "Bookmark Bar Remove";
    case IDC_BOOKMARK_BAR_UNDO:
      return "Bookmark Bar Undo";
    case IDC_BOOKMARK_BAR_REDO:
      return "Bookmark Bar Redo";
    case IDC_BOOKMARK_BAR_ADD_NEW_BOOKMARK:
      return "Bookmark Bar Add New Bookmark";
    case IDC_BOOKMARK_BAR_NEW_FOLDER:
      return "Bookmark Bar New Folder";
    case IDC_BOOKMARK_MANAGER:
      return "Bookmark Manager";
    case IDC_BOOKMARK_BAR_ALWAYS_SHOW:
      return "Bookmark Bar Always Show";
    case IDC_BOOKMARK_BAR_SHOW_APPS_SHORTCUT:
      return "Bookmark Bar Show Apps Shortcut";
    case IDC_BOOKMARK_BAR_SHOW_READING_LIST:
      return "Bookmark Bar Show Reading List";
    case IDC_BOOKMARK_BAR_SHOW_MANAGED_BOOKMARKS:
      return "Bookmark Bar Show Managed Bookmarks";
    case IDC_BOOKMARK_BAR_TRACK_PRICE_FOR_SHOPPING_BOOKMARK:
      return "Bookmark Bar Track Price For Shopping Bookmark";
    case IDC_BOOKMARK_BAR_UNTRACK_PRICE_FOR_SHOPPING_BOOKMARK:
      return "Bookmark Bar Untrack Price For Shopping Bookmark";
    case IDC_CONTENT_CONTEXT_SHARING_CLICK_TO_CALL_SINGLE_DEVICE:
      return "Content Context Sharing Click To Call Single Device";
    case IDC_CONTENT_CONTEXT_SHARING_CLICK_TO_CALL_MULTIPLE_DEVICES:
      return "Content Context Sharing Click To Call Multiple Devices";
    case IDC_CONTENT_CONTEXT_SHARING_SHARED_CLIPBOARD_SINGLE_DEVICE:
      return "Content Context Sharing Shared Clipboard Single Device";
    case IDC_CONTENT_CONTEXT_SHARING_SHARED_CLIPBOARD_MULTIPLE_DEVICES:
      return "Content Context Sharing Shared Clipboard Multiple Devices";
    case IDC_CONTENT_CONTEXT_GENERATE_QR_CODE:
      return "Content Context Generate Qr Code";
    case IDC_CONTENT_CONTEXT_SHARING_SUBMENU:
      return "Content Context Sharing Submenu";
    case IDC_CONTENT_CLIPBOARD_HISTORY_MENU:
      return "Content Clipboard History Menu";
    case IDC_STATUS_TRAY_KEEP_CHROME_RUNNING_IN_BACKGROUND:
      return "Status Tray Keep Chrome Running In Background";
    case IDC_MEDIA_ROUTER_ABOUT:
      return "Media Router About";
    case IDC_MEDIA_ROUTER_HELP:
      return "Media Router Help";
    case IDC_MEDIA_ROUTER_LEARN_MORE:
      return "Media Router Learn More";
    case IDC_MEDIA_ROUTER_ALWAYS_SHOW_TOOLBAR_ACTION:
      return "Media Router Always Show Toolbar Action";
    case IDC_MEDIA_ROUTER_SHOWN_BY_POLICY:
      return "Media Router Shown By Policy";
    case IDC_MEDIA_ROUTER_SHOW_IN_TOOLBAR:
      return "Media Router Show In Toolbar";
    case IDC_MEDIA_ROUTER_TOGGLE_MEDIA_REMOTING:
      return "Media Router Toggle Media Remoting";
    case IDC_MEDIA_TOOLBAR_CONTEXT_SHOW_OTHER_SESSIONS:
      return "Media Toolbar Context Show Other Sessions";
    case IDC_MEDIA_STREAM_DEVICE_STATUS_TRAY:
      return "Media Stream Device Status Tray";
    case IDC_MEDIA_CONTEXT_MEDIA_STREAM_CAPTURE_LIST_FIRST:
      return "Media Context Media Stream Capture List First";
    case IDC_MEDIA_CONTEXT_MEDIA_STREAM_CAPTURE_LIST_LAST:
      return "Media Context Media Stream Capture List Last";
    case IDC_MEDIA_STREAM_DEVICE_ALWAYS_ALLOW:
      return "Media Stream Device Always Allow";
    case IDC_CONTENT_CONTEXT_PROTOCOL_HANDLER_FIRST:
      return "Content Context Protocol Handler First";
    case IDC_CONTENT_CONTEXT_PROTOCOL_HANDLER_LAST:
      return "Content Context Protocol Handler Last";
    case IDC_CONTENT_CONTEXT_PROTOCOL_HANDLER_SETTINGS:
      return "Content Context Protocol Handler Settings";
    case IDC_OPEN_LINK_IN_PROFILE_FIRST:
      return "Open Link In Profile First";
    case IDC_OPEN_LINK_IN_PROFILE_LAST:
      return "Open Link In Profile Last";
    case IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION1:
      return "Content Context Start Smart Selection Action1";
    case IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION2:
      return "Content Context Start Smart Selection Action2";
    case IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION3:
      return "Content Context Start Smart Selection Action3";
    case IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION4:
      return "Content Context Start Smart Selection Action4";
    case IDC_CONTENT_CONTEXT_START_SMART_SELECTION_ACTION5:
      return "Content Context Start Smart Selection Action5";
    case IDC_CONTENT_CONTEXT_ACCESSIBILITY_LABELS_TOGGLE:
      return "Content Context Accessibility Labels Toggle";
    case IDC_CONTENT_CONTEXT_ACCESSIBILITY_LABELS:
      return "Content Context Accessibility Labels";
    case IDC_CONTENT_CONTEXT_ACCESSIBILITY_LABELS_TOGGLE_ONCE:
      return "Content Context Accessibility Labels Toggle Once";
    case IDC_RUN_SCREEN_AI_VISUAL_ANNOTATIONS:
      return "Run Screen Ai Visual Annotations";
    case IDC_TAB_SEARCH:
      return "Tab Search";
    case IDC_TAB_SEARCH_CLOSE:
      return "Tab Search Close";
    case IDC_DEBUG_TOGGLE_TABLET_MODE:
      return "Debug Toggle Tablet Mode";
    case IDC_DEBUG_PRINT_VIEW_TREE:
      return "Debug Print View Tree";
    case IDC_DEBUG_PRINT_VIEW_TREE_DETAILS:
      return "Debug Print View Tree Details";
    case IDC_CONTENT_CONTEXT_AUTOFILL_CUSTOM_FIRST:
      return "Content Context Autofill Custom First";
    case IDC_CONTENT_CONTEXT_AUTOFILL_CUSTOM_LAST:
      return "Content Context Autofill Custom Last";
    case IDC_LIVE_CAPTION:
      return "Live Caption";
    case IDC_SHOW_BRAVE_REWARDS:
      return "Show Brave Rewards";
    case IDC_NEW_TOR_CONNECTION_FOR_SITE:
      return "New Tor Connection For Site";
    case IDC_NEW_OFFTHERECORD_WINDOW_TOR:
      return "New Offtherecord Window Tor";
    case IDC_CONTENT_CONTEXT_OPENLINKTOR:
      return "Content Context Openlinktor";
    case IDC_SHOW_BRAVE_SYNC:
      return "Show Brave Sync";
    case IDC_SHOW_BRAVE_WALLET:
      return "Show Brave Wallet";
    case IDC_ADD_NEW_PROFILE:
      return "Add New Profile";
    case IDC_OPEN_GUEST_PROFILE:
      return "Open Guest Profile";
    case IDC_SHOW_BRAVE_WEBCOMPAT_REPORTER:
      return "Show Brave Webcompat Reporter";
    case IDC_SPEEDREADER_ICON_ONCLICK:
      return "Speedreader Icon Onclick";
    case IDC_SIDEBAR_SHOW_OPTION_MENU:
      return "Sidebar Show Option Menu";
    case IDC_SIDEBAR_SHOW_OPTION_ALWAYS:
      return "Sidebar Show Option Always";
    case IDC_SIDEBAR_SHOW_OPTION_MOUSEOVER:
      return "Sidebar Show Option Mouseover";
    case IDC_SIDEBAR_SHOW_OPTION_NEVER:
      return "Sidebar Show Option Never";
    case IDC_CONTENT_CONTEXT_IMPORT_IPFS:
      return "Content Context Import Ipfs";
    case IDC_CONTENT_CONTEXT_IMPORT_LINK_IPFS:
      return "Content Context Import Link Ipfs";
    case IDC_CONTENT_CONTEXT_IMPORT_IPFS_PAGE:
      return "Content Context Import Ipfs Page";
    case IDC_CONTENT_CONTEXT_IMPORT_IMAGE_IPFS:
      return "Content Context Import Image Ipfs";
    case IDC_CONTENT_CONTEXT_IMPORT_AUDIO_IPFS:
      return "Content Context Import Audio Ipfs";
    case IDC_CONTENT_CONTEXT_IMPORT_VIDEO_IPFS:
      return "Content Context Import Video Ipfs";
    case IDC_CONTENT_CONTEXT_IMPORT_SELECTED_TEXT_IPFS:
      return "Content Context Import Selected Text Ipfs";
    case IDC_APP_MENU_IPFS:
      return "App Menu Ipfs";
    case IDC_APP_MENU_IPFS_PUBLISH_LOCAL_FILE:
      return "App Menu Ipfs Publish Local File";
    case IDC_APP_MENU_IPFS_PUBLISH_LOCAL_FOLDER:
      return "App Menu Ipfs Publish Local Folder";
    case IDC_SHOW_BRAVE_WALLET_PANEL:
      return "Show Brave Wallet Panel";
    case IDC_CLOSE_BRAVE_WALLET_PANEL:
      return "Close Brave Wallet Panel";
    case IDC_SHOW_BRAVE_VPN_PANEL:
      return "Show Brave Vpn Panel";
    case IDC_BRAVE_VPN_MENU:
      return "Brave Vpn Menu";
    case IDC_TOGGLE_BRAVE_VPN_TOOLBAR_BUTTON:
      return "Toggle Brave Vpn Toolbar Button";
    case IDC_SEND_BRAVE_VPN_FEEDBACK:
      return "Send Brave Vpn Feedback";
    case IDC_ABOUT_BRAVE_VPN:
      return "About Brave Vpn";
    case IDC_MANAGE_BRAVE_VPN_PLAN:
      return "Manage Brave Vpn Plan";
    case IDC_TOGGLE_BRAVE_VPN:
      return "Toggle Brave Vpn";
    case IDC_APP_MENU_IPFS_SHARE_LOCAL_FILE:
      return "App Menu Ipfs Share Local File";
    case IDC_APP_MENU_IPFS_SHARE_LOCAL_FOLDER:
      return "App Menu Ipfs Share Local Folder";
    case IDC_APP_MENU_IPFS_OPEN_FILES:
      return "App Menu Ipfs Open Files";
    case IDC_APP_MENU_IPFS_UPDATE_IPNS:
      return "App Menu Ipfs Update Ipns";
    case IDC_CONTENT_CONTEXT_FORCE_PASTE:
      return "Content Context Force Paste";
    case IDC_COPY_CLEAN_LINK:
      return "Copy Clean Link";
    case IDC_TOGGLE_TAB_MUTE:
      return "Toggle Tab Mute";
    case IDC_SIDEBAR_TOGGLE_POSITION:
      return "Sidebar Toggle Position";
    case IDC_CONTENT_CONTEXT_COPY_TEXT_FROM_IMAGE:
      return "Content Context Copy Text From Image";
    case IDC_CONTENT_CONTEXT_IMPORT_IPNS_KEYS_START:
      return "Content Context Import Ipns Keys Start";
    case IDC_CONTENT_CONTEXT_IMPORT_IPNS_KEYS_END:
      return "Content Context Import Ipns Keys End";
    case IDC_BRAVE_BOOKMARK_BAR_SUBMENU:
      return "Brave Bookmark Bar Submenu";
    case IDC_BRAVE_BOOKMARK_BAR_ALWAYS:
      return "Brave Bookmark Bar Always";
    case IDC_BRAVE_BOOKMARK_BAR_NTP:
      return "Brave Bookmark Bar Ntp";
    case IDC_BRAVE_BOOKMARK_BAR_NEVER:
      return "Brave Bookmark Bar Never";
    case IDC_BRAVE_COMMANDS_LAST:
      return "Brave Commands Last";
  }

  NOTREACHED();
  return "";
}
}
  