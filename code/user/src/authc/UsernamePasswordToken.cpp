#include "../../public/UsernamePasswordToken.h"

namespace gemini {
namespace user {

UsernamePasswordToken::UsernamePasswordToken(const String& name,
                                             const String& password)
    : AuthenticationToken(name, password) {}

UsernamePasswordToken::~UsernamePasswordToken() {}

}  // namespace user
}  // namespace gemini