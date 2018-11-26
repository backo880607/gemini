#include "../../include/Errors.h"
#include "../../include/authz/DefaultAuthorizationInfo.h"
#include "../../include/authz/PermissionResolver.h"
#include "../../include/realm/DefaultRealm.h"
#include "../../public/UsernamePasswordToken.h"
#include "../../public/service/IUserService.h"
#include "message/Message.h"

namespace gemini {
namespace user {

void DefaultRealm::authenticate(const AuthenticationToken& token) {
  const UsernamePasswordToken& userToken = (const UsernamePasswordToken&)token;
  ServiceHelper<IUserService> userService;
  User::SPtr user =
      userService->login(token.getPrincipal(), token.getCredentials());
  if (!user.valid()) {
    Message::strong_error<AccountError>(token.getPrincipal());
  }
}

std::shared_ptr<AuthorizationInfo> DefaultRealm::authorization(
    const String& principal) {
  /*std::shared_ptr<User> user =
  UserManager::instance().findByUserName(principal); if (!user) {
          
  }*/

  std::shared_ptr<AuthorizationInfo> info(new DefaultAuthorizationInfo());

  std::set<String> perms;
  // UserManager::instance().findPermissions(user->_id, perms);

  DefaultAuthorizationInfo* defaultInfo = (DefaultAuthorizationInfo*)info.get();
  for (const String& perm : perms) {
    std::shared_ptr<ObjectPermission> p =
        getPermissionResolver()->resolve(perm);
    defaultInfo->addObjectPermission(p);
  }

  return info;
}

}  // namespace user
}  // namespace gemini