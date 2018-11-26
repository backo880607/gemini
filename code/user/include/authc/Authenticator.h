#ifndef GEMINI_USER_Authenticator_INCLUDE
#define GEMINI_USER_Authenticator_INCLUDE
#include "Common.h"

namespace gemini {
namespace user {

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

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Authenticator_INCLUDE