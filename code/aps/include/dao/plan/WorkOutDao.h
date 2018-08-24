#ifndef APS_WorkOutDao_INCLUDE
#define APS_WorkOutDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class WorkOutDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(WorkOutDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_WorkOutDao_INCLUDE