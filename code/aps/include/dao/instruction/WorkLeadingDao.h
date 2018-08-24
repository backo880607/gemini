#ifndef APS_WorkLeadingDao_INCLUDE
#define APS_WorkLeadingDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class WorkLeadingDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(WorkLeadingDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_WorkLeadingDao_INCLUDE