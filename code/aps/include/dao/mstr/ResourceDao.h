#ifndef APS_ResourceDao_INCLUDE
#define APS_ResourceDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class ResourceDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(ResourceDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_ResourceDao_INCLUDE