#include "../include/SecurityMgr.h"
#include "../include/authc/DefaultAuthenticator.h"
#include "../include/authz/DefaultAuthorizer.h"
#include "../public/service/ISessionService.h"

namespace gemini {
namespace user {

SecurityMgr g_securityMgr;
SecurityMgr::SecurityMgr() {
  _authc = new DefaultAuthenticator();
  _authz = new DefaultAuthorizer();
}

SecurityMgr::~SecurityMgr() {
  if (_authc != nullptr) {
    delete _authc;
  }

  if (_authz != nullptr) {
    delete _authz;
  }
}

Session::SPtr SecurityMgr::login(const AuthenticationToken& token) {
  _authc->authenticate(token);
  ServiceHelper<ISessionService> sessionSrv;
  return sessionSrv->createSession();
}

void SecurityMgr::logout(const Session::SPtr& session) {
  session->_stopTime = DateTime::local();
}

Boolean SecurityMgr::isPermitted(const String& principal,
                                 const String& permission) {
  return _authz->isPermitted(principal, permission);
}

}  // namespace user
}  // namespace gemini