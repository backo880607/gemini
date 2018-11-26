#ifndef APS_InventoryDao_INCLUDE
#define APS_InventoryDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class InventoryDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(InventoryDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_InventoryDao_INCLUDE