#include "session/authc/Authenticator.h"

namespace gemini {

Authenticator::Authenticator() {}

Authenticator::~Authenticator() {
  for (Realm* realm : _realms) {
    delete realm;
  }
}

}  // namespace gemini