#ifndef GEMINI_USER_DefaultAuthenticator_INCLUDE
#define GEMINI_USER_DefaultAuthenticator_INCLUDE
#include "Authenticator.h"

namespace gemini {
namespace user {

class DefaultAuthenticator : public Authenticator {
 public:
  DefaultAuthenticator();
  ~DefaultAuthenticator();
  virtual void authenticate(const AuthenticationToken &token);
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DefaultAuthenticator_INCLUDE