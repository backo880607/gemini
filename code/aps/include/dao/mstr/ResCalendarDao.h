#ifndef APS_ResCalendarDao_INCLUDE
#define APS_ResCalendarDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class ResCalendarDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(ResCalendarDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_ResCalendarDao_INCLUDE