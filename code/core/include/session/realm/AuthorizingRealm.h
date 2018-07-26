#ifndef GEMINI_AuthorizingRealm_INCLUDE
#define GEMINI_AuthorizingRealm_INCLUDE
#include "Realm.h"

namespace gemini {

class PermissionResolver;
class AuthorizationInfo;
class AuthorizingRealm : public Realm {
 public:
  AuthorizingRealm();
  ~AuthorizingRealm();

  const PermissionResolver* getPermissionResolver() const {
    return _permissionResolver;
  }
  void setPermissionResolver(const PermissionResolver* resolver) {
    _permissionResolver = resolver;
  }

  Boolean isPermitted(const String& principal, const String& permission);

 protected:
  std::shared_ptr<AuthorizationInfo> getAuthorizationInfo(
      const String& principal);
  // 获取用户权限信息
  virtual std::shared_ptr<AuthorizationInfo> authorization(
      const String& principal) = 0;

 private:
  const PermissionResolver* _permissionResolver;
};

}  // namespace gemini
#endif  // GEMINI_AuthorizingRealm_INCLUDE