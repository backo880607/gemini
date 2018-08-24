#include "../../../bean/mstr/ResCalendar.h"
#include "../../../include/service/mstr/ResCalendarServiceImpl.h"

namespace aps {

gemini::ServiceRegister<ResCalendarServiceImpl, ResCalendarService>
    resCalendar_service_register;
void ResCalendarServiceImpl::init(
    const gemini::SmartPtr<ResCalendar>& resCalendar) const {
  removeRela<ResCalendar::shifts>(resCalendar);
  removeRela<ResCalendar::reses>(resCalendar);
}

}  // namespace aps