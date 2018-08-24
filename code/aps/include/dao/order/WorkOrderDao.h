#ifndef APS_WorkOrderDao_INCLUDE
#define APS_WorkOrderDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class WorkOrderDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(WorkOrderDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_WorkOrderDao_INCLUDE