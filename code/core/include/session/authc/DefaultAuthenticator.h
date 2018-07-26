#ifndef GEMINI_DefaultAuthenticator_INCLUDE
#define GEMINI_DefaultAuthenticator_INCLUDE
#include "Authenticator.h"

namespace gemini {

class DefaultAuthenticator : public Authenticator {
 public:
  DefaultAuthenticator();
  ~DefaultAuthenticator();
  virtual void authenticate(const AuthenticationToken &token);
};

}  // namespace gemini
#endif  // GEMINI_DefaultAuthenticator_INCLUDE