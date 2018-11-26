#ifndef APS_SafeInventoryDao_INCLUDE
#define APS_SafeInventoryDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class SafeInventoryDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(SafeInventoryDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_SafeInventoryDao_INCLUDE