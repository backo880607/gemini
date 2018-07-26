#include "session/UsernamePasswordToken.h"

namespace gemini {

UsernamePasswordToken::UsernamePasswordToken(const String& name,
                                             const String& password)
    : AuthenticationToken(name, password) {}

UsernamePasswordToken::~UsernamePasswordToken() {}

}  // namespace gemini