#ifndef APS_RouteStepDao_INCLUDE
#define APS_RouteStepDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class RouteStepDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(RouteStepDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_RouteStepDao_INCLUDE