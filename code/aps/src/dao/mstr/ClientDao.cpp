#include "../../../bean/mstr/Client.h"
#include "../../../include/dao/mstr/ClientDao.h"

namespace aps {
DECLARE_CLASS_IMPL(ClientDao, gemini::sql::SQLDao)
DAO_REGISTER(ClientDao, Client)
}  // namespace aps