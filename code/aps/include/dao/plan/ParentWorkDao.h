#ifndef APS_ParentWorkDao_INCLUDE
#define APS_ParentWorkDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class ParentWorkDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(ParentWorkDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_ParentWorkDao_INCLUDE