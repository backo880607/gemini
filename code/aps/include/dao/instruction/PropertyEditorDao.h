#ifndef APS_PropertyEditorDao_INCLUDE
#define APS_PropertyEditorDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class PropertyEditorDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(PropertyEditorDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_PropertyEditorDao_INCLUDE