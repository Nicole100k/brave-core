#ifndef BRAVE_BROWSER_UI_COMMANDER_COMMANDER_THROTTLE_H_
#define BRAVE_BROWSER_UI_COMMANDER_COMMANDER_THROTTLE_H_

#include "content/public/browser/navigation_handle.h"
#include "content/public/browser/navigation_throttle.h"

class CommanderThrottle : public content::NavigationThrottle {
 public:
  explicit CommanderThrottle(content::NavigationHandle* handle);
  ~CommanderThrottle() override;

  // content::NavigationThrottle:
  ThrottleCheckResult WillStartRequest() override;
  const char* GetNameForLogging() override;
};

#endif  // BRAVE_BROWSER_UI_COMMANDER_COMMANDER_THROTTLE_H_
