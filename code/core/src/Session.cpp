#include "Session.h"

namespace gemini {

DECLARE_CLASS_IMPL(Session, BaseEntity)

void Session::init() { _daoMgr.init(); }

thread_local Session::SPtr g_subject;
Session::SPtr getSession() { return g_subject; }
void setSession(Session::SPtr session) { g_subject = session; }

}  // namespace gemini