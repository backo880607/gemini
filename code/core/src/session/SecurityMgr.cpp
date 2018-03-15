#include "../../include/session/SecurityMgr.h"
#include "../../include/session/authz/DefaultAuthorizer.h"
#include "../../include/session/authc/DefaultAuthenticator.h"
#include "../../include/cache/Cache.h"

namespace gemini {

SecurityMgr g_securityMgr;
SecurityMgr::SecurityMgr()
{
	_authc = new DefaultAuthenticator();
	_authz = new DefaultAuthorizer();
}

SecurityMgr::~SecurityMgr()
{
	if (_authc != nullptr) {
		delete _authc;
	}

	if (_authz != nullptr) {
		delete _authz;
	}
}

Session::SPtr SecurityMgr::login(const AuthenticationToken& token)
{
	_authc->authenticate(token);
	Session::SPtr session(true);
	session->_startTime = DateTime::local();
	session->_accessTime = session->_startTime;
	return session;
}

void SecurityMgr::logout(const Session::SPtr& session)
{
	session->_stopTime = DateTime::local();
}

Boolean SecurityMgr::isPermitted(const String& principal, const String& permission)
{
	return _authz->isPermitted(principal, permission);
}
}