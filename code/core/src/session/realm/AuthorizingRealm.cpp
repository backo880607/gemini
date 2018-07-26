#include "session/authz/AuthorizationInfo.h"
#include "session/authz/DefaultPermissionResolver.h"
#include "session/realm/AuthorizingRealm.h"

namespace gemini {

AuthorizingRealm::AuthorizingRealm() {
  _permissionResolver = new DefaultPermissionResolver();
}

AuthorizingRealm::~AuthorizingRealm() { delete _permissionResolver; }

Boolean AuthorizingRealm::isPermitted(const String& principal,
                                      const String& permission) {
  std::shared_ptr<ObjectPermission> p =
      getPermissionResolver()->resolve(permission);
  std::shared_ptr<AuthorizationInfo> info = getAuthorizationInfo(principal);
  if (!p || !info) {
    return false;
  }

  const std::vector<std::shared_ptr<ObjectPermission>>& perms =
      info->getObjectPermissions();
  for (std::shared_ptr<ObjectPermission> perm : perms) {
    if (perm->implies(p)) {
      return true;
    }
  }

  return false;
}

std::shared_ptr<AuthorizationInfo> AuthorizingRealm::getAuthorizationInfo(
    const String& principal) {
  std::shared_ptr<AuthorizationInfo> info = authorization(principal);
  return info;
}

}  // namespace gemini