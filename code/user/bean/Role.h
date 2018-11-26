#ifndef GEMINI_USER_Role_INCLUDE
#define GEMINI_USER_Role_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class Permission;
class GEMINI_USER_API Role : public gemini::Entity {
  DECLARE_CLASS(Role, gemini::Entity)

  DECLARE_FIELD(String, name)

  DECLARE_VECTOR(Permission, permissions)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Role_INCLUDE