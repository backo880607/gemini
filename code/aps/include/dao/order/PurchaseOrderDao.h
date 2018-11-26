#ifndef APS_PurchaseOrderDao_INCLUDE
#define APS_PurchaseOrderDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class PurchaseOrderDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(PurchaseOrderDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_PurchaseOrderDao_INCLUDE