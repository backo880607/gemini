#include "../../../include/dao/mstr/ItemDao.h"
#include "../../../bean/mstr/Item.h"

namespace aps {
DECLARE_CLASS_IMPL(ItemDao, gemini::sql::SQLInnerDao)
DAO_REGISTER(ItemDao, Item)
}