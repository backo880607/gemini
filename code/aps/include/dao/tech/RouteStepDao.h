#ifndef APS_RouteStepDao_INCLUDE
#define APS_RouteStepDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class RouteStepDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(RouteStepDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_RouteStepDao_INCLUDE