#ifndef APS_ParentWorkDao_INCLUDE
#define APS_ParentWorkDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class ParentWorkDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(ParentWorkDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_ParentWorkDao_INCLUDE