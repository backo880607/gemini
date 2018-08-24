#ifndef APS_ResourceDao_INCLUDE
#define APS_ResourceDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class ResourceDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(ResourceDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_ResourceDao_INCLUDE