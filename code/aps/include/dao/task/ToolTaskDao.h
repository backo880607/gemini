#ifndef APS_ToolTaskDao_INCLUDE
#define APS_ToolTaskDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class ToolTaskDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(ToolTaskDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_ToolTaskDao_INCLUDE