#include "../../include/dao/PermissionDao.h"

namespace gemini {
namespace user {

DECLARE_CLASS_IMPL(PermissionDao, sql::SQLDao)
DECLARE_CLASS_IMPL(MenuPermissionDao, sql::SQLDao)
DECLARE_CLASS_IMPL(OperationPermissionDao, sql::SQLDao)
DECLARE_CLASS_IMPL(FilePermissionDao, sql::SQLDao)
DECLARE_CLASS_IMPL(ElementPermissionDao, sql::SQLDao)

}  // namespace user
}  // namespace gemini