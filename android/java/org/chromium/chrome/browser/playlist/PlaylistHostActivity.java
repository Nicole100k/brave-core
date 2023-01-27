/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.playlist;

import android.content.Intent;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.ViewModelProvider;

import com.brave.playlist.PlaylistViewModel;
import com.brave.playlist.enums.PlaylistOptions;
import com.brave.playlist.fragment.AllPlaylistFragment;
import com.brave.playlist.fragment.PlaylistFragment;
import com.brave.playlist.listener.PlaylistOptionsListener;
import com.brave.playlist.model.MoveOrCopyModel;
import com.brave.playlist.model.PlaylistItemModel;
import com.brave.playlist.model.PlaylistItemOptionModel;
import com.brave.playlist.model.PlaylistModel;
import com.brave.playlist.model.PlaylistOptionsModel;
import com.brave.playlist.view.bottomsheet.MoveOrCopyToPlaylistBottomSheet;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import org.chromium.base.Log;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.ChromeTabbedActivity;
import org.chromium.chrome.browser.app.BraveActivity;
import org.chromium.chrome.browser.init.AsyncInitializationActivity;
import org.chromium.chrome.browser.playlist.PlaylistBaseActivity;
import org.chromium.chrome.browser.playlist.PlaylistUtils;
import org.chromium.chrome.browser.util.TabUtils;
import org.chromium.playlist.mojom.Playlist;
import org.chromium.playlist.mojom.PlaylistItem;

public class PlaylistHostActivity extends PlaylistBaseActivity implements PlaylistOptionsListener {
    private PlaylistViewModel playlistViewModel;
    @Override
    protected void triggerLayoutInflation() {
        setContentView(R.layout.activity_playlist_host);
        onInitialLayoutInflationComplete();
    }

    @Override
    public void finishNativeInitialization() {
        super.finishNativeInitialization();
        playlistViewModel =
                new ViewModelProvider(PlaylistHostActivity.this).get(PlaylistViewModel.class);

        playlistViewModel.getCreatePlaylistOption().observe(PlaylistHostActivity.this, newName -> {
            if (mPlaylistService != null) {
                Playlist playlist = new Playlist();
                playlist.name = newName;
                playlist.items = new PlaylistItem[0];
                Log.e(PlaylistUtils.TAG, "Name : " + playlist.name);
                mPlaylistService.createPlaylist(playlist, createdPlaylist -> {
                    mPlaylistService.setDefaultPlaylistId(createdPlaylist.id);
                });
                Log.e(PlaylistUtils.TAG, "after Name : " + playlist.name);
                openAllPlaylists(false, null);
            }
        });

        playlistViewModel.getRenamePlaylistOption().observe(
                PlaylistHostActivity.this, renamePlaylistModel -> {
                    if (mPlaylistService != null) {
                        mPlaylistService.renamePlaylist(renamePlaylistModel.getPlaylistId(),
                                renamePlaylistModel.getNewName(), updatedPlaylist -> {
                                    Log.e(PlaylistUtils.TAG,
                                            "after rename Name : " + updatedPlaylist.name);
                                    openPlaylist(updatedPlaylist.id, false);
                                });
                    }
                });

        playlistViewModel.getPlaylistToOpen().observe(PlaylistHostActivity.this, playlistId -> {
            if (mPlaylistService != null) {
                openPlaylist(playlistId, true);
            }
        });

        playlistViewModel.getDeletePlaylistItems().observe(
                PlaylistHostActivity.this, playlistItems -> {
                    if (mPlaylistService != null) {
                        for (PlaylistItemModel playlistItem : playlistItems.getItems()) {
                            mPlaylistService.removeItemFromPlaylist(
                                    playlistItems.getId(), playlistItem.getId());
                        }
                        openPlaylist(playlistItems.getId(), false);
                    }
                });

        playlistViewModel.getPlaylistOption().observe(
                PlaylistHostActivity.this, playlistOptionsModel -> {
                    if (mPlaylistService != null) {
                        PlaylistOptions option = playlistOptionsModel.getOptionType();
                        if (option == PlaylistOptions.EDIT_PLAYLIST) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.EDIT_PLAYLIST");
                        } else if (option == PlaylistOptions.RENAME_PLAYLIST) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.RENAME_PLAYLIST");
                        } else if (option == PlaylistOptions.REMOVE_PLAYLIST_OFFLINE_DATA) {
                            Log.e(PlaylistUtils.TAG,
                                    "PlaylistOptions.REMOVE_PLAYLIST_OFFLINE_DATA");
                            if (mPlaylistService != null
                                    && playlistOptionsModel.getPlaylistModel() != null) {
                                mPlaylistService.removeLocalDataForItemsInPlaylist(
                                        playlistOptionsModel.getPlaylistModel().getId());
                            }
                        } else if (option == PlaylistOptions.DOWNLOAD_PLAYLIST_FOR_OFFLINE_USE) {
                            Log.e(PlaylistUtils.TAG,
                                    "PlaylistOptions.DOWNLOAD_PLAYLIST_FOR_OFFLINE_USE");
                        } else if (option == PlaylistOptions.DELETE_PLAYLIST) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.DELETE_PLAYLIST");
                            if (mPlaylistService != null
                                    && playlistOptionsModel.getPlaylistModel() != null) {
                                mPlaylistService.removePlaylist(
                                        playlistOptionsModel.getPlaylistModel().getId());
                                openAllPlaylists(false, null);
                            }
                        }
                    }
                });

        playlistViewModel.getAllPlaylistOption().observe(
                PlaylistHostActivity.this, playlistOptionsModel -> {
                    if (mPlaylistService != null) {
                        PlaylistOptions option = playlistOptionsModel.getOptionType();
                        if (option == PlaylistOptions.REMOVE_ALL_OFFLINE_DATA) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.REMOVE_ALL_OFFLINE_DATA");
                            if (mPlaylistService != null
                                    && playlistOptionsModel.getPlaylistModel() != null) {
                                mPlaylistService.removeLocalDataForItemsInPlaylist(
                                        playlistOptionsModel.getPlaylistModel().getId());
                            }
                        } else if (option
                                == PlaylistOptions.DOWNLOAD_ALL_PLAYLISTS_FOR_OFFLINE_USE) {
                            Log.e(PlaylistUtils.TAG,
                                    "PlaylistOptions.DOWNLOAD_ALL_PLAYLISTS_FOR_OFFLINE_USE");
                        }
                    }
                });

        playlistViewModel.getPlaylistItemOption().observe(
                PlaylistHostActivity.this, playlistItemOption -> {
                    if (mPlaylistService != null) {
                        PlaylistOptions option = playlistItemOption.getPlaylistOptions();
                        if (option == PlaylistOptions.MOVE_PLAYLIST_ITEM) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.MOVE_PLAYLIST_ITEM");
                            openAllPlaylists(true, playlistItemOption);
                        } else if (option == PlaylistOptions.COPY_PLAYLIST_ITEM) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.COPY_PLAYLIST_ITEM");
                            openAllPlaylists(true, playlistItemOption);
                        } else if (option == PlaylistOptions.DELETE_ITEMS_OFFLINE_DATA) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.DELETE_ITEMS_OFFLINE_DATA");
                            mPlaylistService.removeLocalDataForItem(
                                    playlistItemOption.getPlaylistItemModel().getId());
                        } else if (option == PlaylistOptions.SHARE_PLAYLIST_ITEM) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.SHARE_PLAYLIST_ITEM");
                        } else if (option == PlaylistOptions.OPEN_IN_NEW_TAB) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.OPEN_IN_NEW_TAB");
                            openPlaylistInTab(false,
                                    playlistItemOption.getPlaylistItemModel().getPageSource());
                        } else if (option == PlaylistOptions.OPEN_IN_PRIVATE_TAB) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.OPEN_IN_PRIVATE_TAB");
                            openPlaylistInTab(true,
                                    playlistItemOption.getPlaylistItemModel().getPageSource());
                        } else if (option == PlaylistOptions.DELETE_PLAYLIST_ITEM) {
                            Log.e(PlaylistUtils.TAG, "PlaylistOptions.DELETE_PLAYLIST_ITEM");
                            mPlaylistService.removeItemFromPlaylist(
                                    playlistItemOption.getPlaylistId(),
                                    playlistItemOption.getPlaylistItemModel().getId());
                        }
                    }
                });

        if (getIntent() != null && getIntent().getStringExtra(PlaylistUtils.PLAYLIST_ID) != null) {
            String playlistId = getIntent().getStringExtra(PlaylistUtils.PLAYLIST_ID);
            if (playlistId.equals("all")) {
                openAllPlaylists(false, null);
            } else {
                openPlaylist(playlistId, true);
            }
        }
    }

    private void openPlaylist(String playlistId, boolean recreateFragment) {
        if (mPlaylistService != null) {
            mPlaylistService.getPlaylist(playlistId, playlist -> {
                JSONObject playlistJsonObject = new JSONObject();
                try {
                    playlistJsonObject.put("id", playlist.id);
                    playlistJsonObject.put("name", playlist.name);
                    JSONArray playlistItemsJsonArray = new JSONArray();
                    for (PlaylistItem playlistItem : playlist.items) {
                        JSONObject playlistItemObject = new JSONObject();
                        playlistItemObject.put("id", playlistItem.id);
                        playlistItemObject.put("name", playlistItem.name);
                        playlistItemObject.put("page_source", playlistItem.pageSource.url);
                        playlistItemObject.put("media_path", playlistItem.mediaPath.url);
                        playlistItemObject.put("media_src", playlistItem.mediaSource.url);
                        playlistItemObject.put("thumbnail_path", playlistItem.thumbnailPath.url);
                        playlistItemObject.put("cached", playlistItem.cached);
                        playlistItemObject.put("author", playlistItem.author);
                        playlistItemObject.put("duration", playlistItem.duration);
                        playlistItemsJsonArray.put(playlistItemObject);
                    }
                    playlistJsonObject.put("items", playlistItemsJsonArray);
                    if (playlistViewModel != null) {
                        playlistViewModel.setPlaylistData(playlistJsonObject.toString(2));
                    }

                    if (recreateFragment) {
                        PlaylistFragment playlistFragment = new PlaylistFragment();
                        getSupportFragmentManager()
                                .beginTransaction()
                                .replace(R.id.fragment_container_view_tag, playlistFragment)
                                .commit();
                    }
                } catch (JSONException e) {
                    Log.e(PlaylistUtils.TAG, "PlaylistHostActivity -> JSONException error " + e);
                }
            });
        }
    }

    private void openAllPlaylists(
            boolean showMoveOrCopy, PlaylistItemOptionModel playlistItemOptionModel) {
        if (mPlaylistService != null) {
            mPlaylistService.getAllPlaylists(playlists -> {
                try {
                    JSONArray playlistsJsonArray = new JSONArray();
                    for (Playlist playlist : playlists) {
                        JSONObject playlistJsonObject = new JSONObject();

                        playlistJsonObject.put("id", playlist.id);
                        playlistJsonObject.put("name", playlist.name);
                        JSONArray playlistItemsJsonArray = new JSONArray();
                        for (PlaylistItem playlistItem : playlist.items) {
                            JSONObject playlistItemObject = new JSONObject();
                            playlistItemObject.put("id", playlistItem.id);
                            playlistItemObject.put("name", playlistItem.name);
                            playlistItemObject.put("page_source", playlistItem.pageSource.url);
                            playlistItemObject.put("media_path", playlistItem.mediaPath.url);
                            playlistItemObject.put("media_src", playlistItem.mediaSource.url);
                            playlistItemObject.put(
                                    "thumbnail_path", playlistItem.thumbnailPath.url);
                            playlistItemObject.put("cached", playlistItem.cached);
                            playlistItemObject.put("author", playlistItem.author);
                            playlistItemObject.put("duration", playlistItem.duration);
                            playlistItemsJsonArray.put(playlistItemObject);
                        }
                        playlistJsonObject.put("items", playlistItemsJsonArray);
                        Log.e(PlaylistUtils.TAG, "playlistJsonObject : " + playlistJsonObject);
                        playlistsJsonArray.put(playlistJsonObject);
                    }
                    Log.e(PlaylistUtils.TAG, "playlistsJsonArray : " + playlistsJsonArray);
                    if (playlistViewModel != null) {
                        playlistViewModel.setAllPlaylistData(playlistsJsonArray.toString(2));
                    }

                    if (!showMoveOrCopy) {
                        AllPlaylistFragment allPlaylistFragment = new AllPlaylistFragment();
                        getSupportFragmentManager()
                                .beginTransaction()
                                .replace(R.id.fragment_container_view_tag, allPlaylistFragment)
                                .commit();
                    } else {
                        MoveOrCopyModel moveOrCopyModel =
                                new MoveOrCopyModel(playlistItemOptionModel.getPlaylistOptions(),
                                        playlistItemOptionModel.getPlaylistId(), "");
                        new MoveOrCopyToPlaylistBottomSheet(moveOrCopyModel)
                                .show(getSupportFragmentManager(), null);
                    }
                } catch (JSONException e) {
                    Log.e(PlaylistUtils.TAG, "PlaylistHostActivity -> JSONException error " + e);
                }
            });
        }
    }

    @Override
    public void onOptionClicked(PlaylistOptionsModel playlistOptionsModel) {
        Log.e(PlaylistUtils.TAG,
                "PlaylistOptionsModel type : " + playlistOptionsModel.getOptionType());
        if (PlaylistOptions.DELETE_PLAYLIST == playlistOptionsModel.getOptionType()) {
            if (mPlaylistService != null && playlistOptionsModel.getPlaylistModel() != null) {
                mPlaylistService.removePlaylist(playlistOptionsModel.getPlaylistModel().getId());
                finish();
            }
        }
    }

    private void openPlaylistInTab(boolean isIncognito, String url) {
        finish();
        TabUtils.openUrlInNewTab(isIncognito, url);
    }
}
