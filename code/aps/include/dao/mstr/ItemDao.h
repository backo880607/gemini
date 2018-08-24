#ifndef GEMINI_APS_ItemDao_INCLUDE
#define GEMINI_APS_ItemDao_INCLUDE
#include "../../../../sql/public/SQLDao.h"

namespace aps {

class ItemDao : public gemini::sql::SQLInnerDao {
  DECLARE_CLASS(ItemDao, gemini::sql::SQLInnerDao)
};

}  // namespace aps
#endif  // GEMINI_APS_ItemDao_INCLUDE