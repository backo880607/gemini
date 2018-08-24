#ifndef APS_ResCalendarService_INCLUDE
#define APS_ResCalendarService_INCLUDE
#include "service/IBaseService.h"

namespace aps {

class ResCalendar;
class ResCalendarService {
 public:
  virtual void init(const gemini::SmartPtr<ResCalendar>& resCalendar) const = 0;
};

}  // namespace aps
#endif  // !APS_ResCalendarService_INCLUDE