#include "brave/browser/ui/commander/commander_throttle.h"
#include <cstdint>
#include <string>
#include <vector>

#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/commander/commander.h"
#include "chrome/browser/ui/commander/commander_backend.h"
#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/navigation_throttle.h"

const char kCommanderThrottleName[] = "CommanderThrottle";

CommanderThrottle::CommanderThrottle(content::NavigationHandle* handle)
    : content::NavigationThrottle(handle) {}

CommanderThrottle::~CommanderThrottle() = default;

content::NavigationThrottle::ThrottleCheckResult
CommanderThrottle::WillStartRequest() {
  if (navigation_handle()->GetURL().SchemeIs("brave-command")) {
    auto* commander = commander::Commander::Get();
    if (commander) {
      auto* backend = commander->backend();
      if (backend) {
        auto url = navigation_handle()->GetURL();
        LOG(ERROR) << "URL: " << url.spec() << ", Path: " << url.path();
        std::vector<std::string> parts = base::SplitString(
            url.path(), "/", base::KEEP_WHITESPACE, base::SPLIT_WANT_NONEMPTY);
        LOG(ERROR) << "Parts: " << parts.size();
        uint32_t session_id;
        uint32_t command_index;
        if (parts.size() >= 2 && base::StringToUint(parts[0], &session_id) &&
            base::StringToUint(parts[1], &command_index)) {
          LOG(ERROR) << "Selected command: " << session_id << ", " << command_index;
          commander->backend()->OnCommandSelected(command_index, session_id);
        }
      }
    }
    LOG(ERROR) << "Navigated to: " << navigation_handle()->GetURL().spec();
    return ThrottleCheckResult(ThrottleAction::CANCEL_AND_IGNORE);
  }
  return ThrottleCheckResult(ThrottleAction::PROCEED);
}

const char* CommanderThrottle::GetNameForLogging() {
  return kCommanderThrottleName;
}

void CommanderThrottle::ToggleForBrowser(Browser* browser) {
  browser->SetFocusToLocationBar();
}

void CommanderThrottle::Show(Browser* browser) {
  browser->SetFocusToLocationBar();
}

void CommanderThrottle::Hide() {
  // no op
}
