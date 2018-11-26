#include "Permission.h"

namespace gemini {
namespace user {

DECLARE_CLASS_IMPL(Permission, gemini::Entity)
DECLARE_CLASS_IMPL(MenuPermission, Permission)
DECLARE_CLASS_IMPL(OperationPermission, Permission)
DECLARE_CLASS_IMPL(FilePermission, Permission)
DECLARE_CLASS_IMPL(ElementPermission, Permission)

}  // namespace user
}  // namespace gemini