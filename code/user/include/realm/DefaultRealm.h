#ifndef GEMINI_USER_DefaultRealm_INCLUDE
#define GEMINI_USER_DefaultRealm_INCLUDE
#include "AuthorizingRealm.h"

namespace gemini {
namespace user {

class DefaultRealm : public AuthorizingRealm {
 public:
  virtual void authenticate(const AuthenticationToken& token) override;
  virtual std::shared_ptr<AuthorizationInfo> authorization(
      const String& principal) override;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DefaultRealm_INCLUDE