#ifndef APS_TransTimeDao_INCLUDE
#define APS_TransTimeDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class TransTimeDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(TransTimeDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_TransTimeDao_INCLUDE