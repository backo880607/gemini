#ifndef APS_WorkResDao_INCLUDE
#define APS_WorkResDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class WorkResDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(WorkResDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_WorkResDao_INCLUDE