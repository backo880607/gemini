#include "../../include/authc/Authenticator.h"

namespace gemini {
namespace user {

Authenticator::Authenticator() {}

Authenticator::~Authenticator() {
  for (Realm* realm : _realms) {
    delete realm;
  }
}

}  // namespace user
}  // namespace gemini