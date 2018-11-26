#ifndef APS_MinInventoryDao_INCLUDE
#define APS_MinInventoryDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class MinInventoryDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(MinInventoryDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_MinInventoryDao_INCLUDE