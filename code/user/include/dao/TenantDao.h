#ifndef GEMINI_USER_TenantDao_INCLUDE
#define GEMINI_USER_TenantDao_INCLUDE
#include "../../../sql/public/SQLDao.h"

namespace gemini {
namespace user {

class TenantDao : public sql::SQLDao {
  DECLARE_CLASS(TenantDao, sql::SQLDao)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_TenantDao_INCLUDE