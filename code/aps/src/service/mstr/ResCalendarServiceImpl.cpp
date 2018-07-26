#include "../../../include/service/mstr/ResCalendarServiceImpl.h"
#include "../../../bean/mstr/ResCalendar.h"

namespace aps {

void ResCalendarServiceImpl::init(
    const gemini::SmartPtr<ResCalendar>& resCalendar) const {
  removeRela<ResCalendar::shifts>(resCalendar);
  removeRela<ResCalendar::reses>(resCalendar);
}

}  // namespace aps