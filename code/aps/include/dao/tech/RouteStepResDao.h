#ifndef APS_RouteStepResDao_INCLUDE
#define APS_RouteStepResDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class RouteStepResDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(RouteStepResDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_RouteStepResDao_INCLUDE