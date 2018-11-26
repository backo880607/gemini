#ifndef APS_BatchElementDao_INCLUDE
#define APS_BatchElementDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class BatchElementDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(BatchElementDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_BatchElementDao_INCLUDE