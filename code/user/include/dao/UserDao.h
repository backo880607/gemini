#ifndef GEMINI_USER_UserDao_INCLUDE
#define GEMINI_USER_UserDao_INCLUDE
#include "../../../sql/public/SQLDao.h"

namespace gemini {
namespace user {

class UserDao : public sql::SQLDao {
  DECLARE_CLASS(UserDao, sql::SQLDao)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_UserDao_INCLUDE