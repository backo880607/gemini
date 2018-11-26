#ifndef APS_WorkRelDao_INCLUDE
#define APS_WorkRelDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class WorkRelDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(WorkRelDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_WorkRelDao_INCLUDE