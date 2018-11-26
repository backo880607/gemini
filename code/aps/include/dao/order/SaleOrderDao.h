#ifndef APS_SaleOrderDao_INCLUDE
#define APS_SaleOrderDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class SaleOrderDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(SaleOrderDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_SaleOrderDao_INCLUDE