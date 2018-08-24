#ifndef GEMINI_SecurityMgr_INCLUDE
#define GEMINI_SecurityMgr_INCLUDE
#include "../../include/dao/DaoMgr.h"
#include "../../public/session/AuthenticationToken.h"
#include "../../public/session/Session.h"

namespace gemini {

class Security {
 public:
  Security();
  ~Security();

  DaoMgr &getDaoMgr() { return _daoMgr; }

 private:
  DaoMgr _daoMgr;
};
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

}  // namespace gemini
#endif  // GEMINI_SecurityMgr_INCLUDE