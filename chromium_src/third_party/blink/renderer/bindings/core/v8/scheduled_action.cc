/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "third_party/blink/renderer/bindings/core/v8/scheduled_action.h"

#include "brave/components/brave_page_graph/common/buildflags.h"
#include "brave/v8/include/v8-isolate-page-graph-utils.h"
#include "third_party/blink/renderer/core/probe/core_probes.h"

#define BRAVE_SCHEDULED_ACTION_STRING_CODE_CONSTRUCTOR                   \
  IF_BUILDFLAG(ENABLE_BRAVE_PAGE_GRAPH, {                                \
    if (CoreProbeSink::HasAgentsGlobal(CoreProbeSink::kPageGraph)) {     \
      parent_script_id_ =                                                \
          v8::page_graph::GetExecutingScript(script_state->GetIsolate()) \
              .script_id;                                                \
    }                                                                    \
  })

#include "src/third_party/blink/renderer/bindings/core/v8/scheduled_action.cc"

#undef BRAVE_SCHEDULED_ACTION_STRING_CODE_CONSTRUCTOR

namespace blink {

ScriptFetchOptions ScheduledAction::GetScriptFetchOptions() const {
  ScriptFetchOptions script_fetch_options;
  script_fetch_options.SetParentScriptId(parent_script_id_);
  return script_fetch_options;
}

}  // namespace blink
