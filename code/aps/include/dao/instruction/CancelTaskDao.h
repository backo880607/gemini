#ifndef APS_CancelTaskDao_INCLUDE
#define APS_CancelTaskDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class CancelTaskDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(CancelTaskDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_CancelTaskDao_INCLUDE