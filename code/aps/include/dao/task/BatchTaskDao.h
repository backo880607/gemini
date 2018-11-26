#ifndef APS_BatchTaskDao_INCLUDE
#define APS_BatchTaskDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class BatchTaskDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(BatchTaskDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_BatchTaskDao_INCLUDE