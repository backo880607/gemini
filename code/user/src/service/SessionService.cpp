#include "../../include/service/SessionService.h"
#include "Session.h"

namespace gemini {
namespace user {
gemini::ServiceRegister<SessionService, ISessionService> session_service_register;
SmartPtr<Session> SessionService::createSession() const {
  Session::SPtr session = create<Session>();
  session->_startTime = DateTime::local();
  session->_accessTime = session->_startTime;
  return session;
}

}
}  // namespace gemini