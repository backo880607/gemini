#include "../../public/session/Subject.h"
#include "../../include/session/SecurityMgr.h"

namespace gemini {

thread_local Subject g_subject;
Subject::Subject()
{

}

Subject::~Subject()
{

}

const Subject& Subject::get()
{
	return g_subject;
}

Boolean Subject::isAuthenticated() const
{
	return _session != nullptr;
}

void Subject::login(const AuthenticationToken& token) const {
	const_cast<Session::SPtr&>(_session) = g_securityMgr.login(token);
}

void Subject::logout() const
{
	g_securityMgr.logout(_session);
	const_cast<Session::SPtr&>(_session) = nullptr;
}

Boolean Subject::isPermitted(const Char* permission) const
{
	return true;
}

}