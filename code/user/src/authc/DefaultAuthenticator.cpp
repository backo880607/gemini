#include "../../include/authc/DefaultAuthenticator.h"
#include "../../include/realm/DefaultRealm.h"

namespace gemini {
namespace user {

DefaultAuthenticator::DefaultAuthenticator() {
  _realms.push_back(new DefaultRealm());
}

DefaultAuthenticator::~DefaultAuthenticator() {}

void DefaultAuthenticator::authenticate(const AuthenticationToken& token) {
  for (Realm* realm : _realms) {
    if (!realm->supports(token)) {
      continue;
    }

    realm->authenticate(token);
  }
}

}  // namespace user
}  // namespace gemini