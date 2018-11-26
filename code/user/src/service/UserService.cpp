#include "../../include/service/UserService.h"

namespace gemini {
namespace user {

gemini::ServiceRegister<UserService, IUserService> user_service_register;
User::SPtr UserService::login(const String& principal,
                              const String& password) const {
  if (principal == "root") {
    if (password == "880607") {
      User::SPtr user = createTemp<User>();
      user->_name = principal;
      return user;
    }
  }
  return nullptr;
}

}  // namespace user
}  // namespace gemini