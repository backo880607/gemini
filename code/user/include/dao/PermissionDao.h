#ifndef GEMINI_USER_PermissionDao_INCLUDE
#define GEMINI_USER_PermissionDao_INCLUDE
#include "../../../data/public/SQLDao.h"

namespace gemini {
namespace user {

class PermissionDao : public sql::SQLDao {
  DECLARE_CLASS(PermissionDao, sql::SQLDao)
};

class MenuPermissionDao : public sql::SQLDao {
  DECLARE_CLASS(MenuPermissionDao, sql::SQLDao)
};

class OperationPermissionDao : public sql::SQLDao {
  DECLARE_CLASS(OperationPermissionDao, sql::SQLDao)
};

class FilePermissionDao : public sql::SQLDao {
  DECLARE_CLASS(FilePermissionDao, sql::SQLDao)
};

class ElementPermissionDao : public sql::SQLDao {
  DECLARE_CLASS(ElementPermissionDao, sql::SQLDao)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_PrivilegeDao_INCLUDE