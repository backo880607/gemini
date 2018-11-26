#ifndef GEMINI_USER_ISessionService_INCLUDE
#define GEMINI_USER_ISessionService_INCLUDE
#include "service/IBaseService.h"

namespace gemini {
class Session;
namespace user {

class ISessionService {
 public:
  virtual SmartPtr<Session> createSession() const = 0;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_ISessionService_INCLUDE