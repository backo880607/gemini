#include "session/AuthenticationToken.h"

namespace gemini {

AuthenticationToken::AuthenticationToken(const String& principal,
                                         const String& credentials)
    : _principal(principal), _credentials(credentials) {}

AuthenticationToken::~AuthenticationToken() {}

}  // namespace gemini