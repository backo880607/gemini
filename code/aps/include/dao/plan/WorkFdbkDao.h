#ifndef APS_WorkFdbkDao_INCLUDE
#define APS_WorkFdbkDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class WorkFdbkDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(WorkFdbkDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_WorkFdbkDao_INCLUDE