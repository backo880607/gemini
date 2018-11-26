#include "../../include/authz/DefaultAuthorizer.h"
#include "../../include/realm/DefaultRealm.h"

namespace gemini {
namespace user {

DefaultAuthorizer::DefaultAuthorizer() {
  _realms.push_back(std::shared_ptr<Realm>(new DefaultRealm()));
}

DefaultAuthorizer::~DefaultAuthorizer() {}

Boolean DefaultAuthorizer::isPermitted(const String& principal,
                                       const String& permission) {
  for (std::shared_ptr<Realm>& realm : _realms) {
    AuthorizingRealm* authz = (AuthorizingRealm*)realm.get();
    if (authz->isPermitted(principal, permission)) {
      return true;
    }
  }

  return false;
}

}  // namespace user
}  // namespace gemini