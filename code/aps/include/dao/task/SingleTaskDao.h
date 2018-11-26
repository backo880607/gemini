#ifndef APS_SingleTaskDao_INCLUDE
#define APS_SingleTaskDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class SingleTaskDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(SingleTaskDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_SingleTaskDao_INCLUDE