#ifndef APS_CommandDao_INCLUDE
#define APS_CommandDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class CommandDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(CommandDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_CommandDao_INCLUDE