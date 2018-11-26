#ifndef APS_RouteDao_INCLUDE
#define APS_RouteDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class RouteDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(RouteDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_RouteDao_INCLUDE