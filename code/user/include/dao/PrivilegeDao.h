#ifndef GEMINI_USER_PrivilegeDao_INCLUDE
#define GEMINI_USER_PrivilegeDao_INCLUDE
#include "../../../sql/public/SQLDao.h"

namespace gemini {
namespace user {

class PrivilegeDao : public sql::SQLDao {
  DECLARE_CLASS(PrivilegeDao, sql::SQLDao)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_PrivilegeDao_INCLUDE