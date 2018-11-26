#ifndef GEMINI_USER_Realm_INCLUDE
#define GEMINI_USER_Realm_INCLUDE
#include "Common.h"

namespace gemini {
namespace user {

class AuthenticationToken;
class Realm {
 public:
  Boolean supports(const AuthenticationToken& token);
  virtual void authenticate(const AuthenticationToken& token) = 0;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Realm_INCLUDE