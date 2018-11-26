#ifndef GEMINI_USER_SessionService_INCLUDE
#define GEMINI_USER_SessionService_INCLUDE
#include "../../public/service/ISessionService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class SessionService : public BaseService, public ISessionService {
 public:
  virtual SmartPtr<Session> createSession() const override;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_SessionService_INCLUDE