#ifndef APS_ResCalendarServiceImpl_INCLUDE
#define APS_ResCalendarServiceImpl_INCLUDE
#include "../../../public/service/mstr/ResCalendarService.h"
#include "service/BaseService.h"

namespace aps {

class ResCalendarServiceImpl : public gemini::BaseService, ResCalendarService {
  virtual void init(const gemini::SmartPtr<ResCalendar>& resCalendar) const;
};

}  // namespace aps
#endif  // !APS_ResCalendarServiceImpl_INCLUDE