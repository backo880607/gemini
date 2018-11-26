#ifndef GEMINI_USER_User_INCLUDE
#define GEMINI_USER_User_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class Role;
class GEMINI_USER_API User : public gemini::Entity {
  DECLARE_CLASS(User, gemini::Entity)

  DECLARE_FIELD(String, name)
  DECLARE_FIELD(String, password)
  DECLARE_FIELD(String, email)
  DECLARE_FIELD(String, phone)
  DECLARE_FIELD(String, address)

  DECLARE_VECTOR(Role, roles)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_User_INCLUDE