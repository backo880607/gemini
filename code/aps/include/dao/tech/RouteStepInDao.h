#ifndef APS_RouteStepInDao_INCLUDE
#define APS_RouteStepInDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class RouteStepInDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(RouteStepInDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_RouteStepInDao_INCLUDE