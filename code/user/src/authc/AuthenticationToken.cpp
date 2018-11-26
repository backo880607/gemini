#include "../../public/AuthenticationToken.h"

namespace gemini {
namespace user {

AuthenticationToken::AuthenticationToken(const String& principal,
                                         const String& credentials)
    : _principal(principal), _credentials(credentials) {}

AuthenticationToken::~AuthenticationToken() {}

}  // namespace user
}  // namespace gemini