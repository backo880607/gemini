#ifndef APS_WorkInDao_INLCUDE
#define APS_WorkInDao_INLCUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class WorkInDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(WorkInDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_WorkInDao_INLCUDE