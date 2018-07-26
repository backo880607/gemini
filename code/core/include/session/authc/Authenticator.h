#ifndef GEMINI_Authenticator_INCLUDE
#define GEMINI_Authenticator_INCLUDE
#include "../../../public/Common.h"

namespace gemini {

class Realm;
class AuthenticationToken;
class Authenticator {
 public:
  Authenticator();
  virtual ~Authenticator();
  virtual void authenticate(const AuthenticationToken &token) = 0;

 protected:
  std::vector<Realm *> _realms;
};

}  // namespace gemini
#endif  // GEMINI_Authenticator_INCLUDE