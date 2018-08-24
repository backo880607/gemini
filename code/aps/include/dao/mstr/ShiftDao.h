#ifndef APS_ShiftDao_INCLUDE
#define APS_ShiftDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class ShiftDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(ShiftDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_ShiftDao_INCLUDE