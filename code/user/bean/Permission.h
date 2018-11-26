#ifndef GEMINI_USER_Permission_INCLUDE
#define GEMINI_USER_Permission_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class GEMINI_USER_API Permission : public gemini::Entity {
  DECLARE_CLASS(Permission, gemini::Entity)
};

/**
 * @brief 菜单的访问权限
 *
 */
class GEMINI_USER_API MenuPermission : public Permission {
  DECLARE_CLASS(MenuPermission, Permission)
};

/**
 * @brief 功能模块的操作权限
 *
 */
class GEMINI_USER_API OperationPermission : public Permission {
  DECLARE_CLASS(OperationPermission, Permission)
};

/**
 * @brief 文件的修改权限
 *
 */
class GEMINI_USER_API FilePermission : public Permission {
  DECLARE_CLASS(FilePermission, Permission)
};

/**
 * @brief 页面元素的可见性控制
 *
 */
class GEMINI_USER_API ElementPermission : public Permission {
  DECLARE_CLASS(ElementPermission, Permission)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Permission_INCLUDE