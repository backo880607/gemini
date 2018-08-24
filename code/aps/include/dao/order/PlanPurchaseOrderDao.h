#ifndef APS_PlanPurchaseOrderDao_INCLUDE
#define APS_PlanPurchaseOrderDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class PlanPurchaseOrderDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(PlanPurchaseOrderDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_PlanPurchaseOrderDao_INCLUDE