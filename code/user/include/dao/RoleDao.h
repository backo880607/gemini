#ifndef GEMINI_USER_RoleDao_INCLUDE
#define GEMINI_USER_RoleDao_INCLUDE
#include "../../../sql/public/SQLDao.h"

namespace gemini {
namespace user {

class RoleDao : public sql::SQLDao {
  DECLARE_CLASS(RoleDao, sql::SQLDao)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_RoleDao_INCLUDE