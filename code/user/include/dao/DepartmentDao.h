#ifndef GEMINI_USER_DepartmentDao_INCLUDE
#define GEMINI_USER_DepartmentDao_INCLUDE
#include "../../../data/public/SQLDao.h"

namespace gemini {
namespace user {

class DepartmentDao : public sql::SQLDao {
  DECLARE_CLASS(DepartmentDao, sql::SQLDao)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DepartmentDao_INCLUDE