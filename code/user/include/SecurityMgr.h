#ifndef GEMINI_USER_SecurityMgr_INCLUDE
#define GEMINI_USER_SecurityMgr_INCLUDE
#include "../public/AuthenticationToken.h"
#include "Session.h"

namespace gemini {
namespace user {

class Authenticator;
class Authorizer;
class SecurityMgr {
 public:
  SecurityMgr();
  ~SecurityMgr();

  Session::SPtr login(const AuthenticationToken &token);
  void logout(const Session::SPtr &session);

  Boolean isPermitted(const String &principal, const String &permission);

 private:
  Authenticator *_authc;
  Authorizer *_authz;
};
extern SecurityMgr g_securityMgr;

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_SecurityMgr_INCLUDE