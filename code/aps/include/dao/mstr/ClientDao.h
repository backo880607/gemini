#ifndef APS_ClientDao_INCLUDE
#define APS_ClientDao_INCLUDE
#include "../../../../data/public/SQLDao.h"

namespace aps {

class ClientDao : public gemini::sql::SQLDao {
  DECLARE_CLASS(ClientDao, gemini::sql::SQLDao)
};

}  // namespace aps
#endif  // APS_ClientDao_INCLUDE