#ifndef APS_PlanWorkOrderDao_INCLUDE
#define APS_PlanWorkOrderDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class PlanWorkOrderDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(PlanWorkOrderDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_PlanWorkOrderDao_INCLUDE