#ifndef GEMINI_USER_UsernamePasswordToken_INCLUDE
#define GEMINI_USER_UsernamePasswordToken_INCLUDE
#include "AuthenticationToken.h"

namespace gemini {
namespace user {

class GEMINI_USER_API UsernamePasswordToken : public AuthenticationToken {
 public:
  UsernamePasswordToken(const String& name, const String& password);
  ~UsernamePasswordToken();
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_UsernamePasswordToken_INCLUDE