#ifndef APS_WorkDao_INCLUDE
#define APS_WorkDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class WorkDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(WorkDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_WorkDao_INCLUDE