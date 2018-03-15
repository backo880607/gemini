#ifndef GEMINI_DefaultRealm_INCLUDE
#define GEMINI_DefaultRealm_INCLUDE
#include "AuthorizingRealm.h"

namespace gemini {

class DefaultRealm : public AuthorizingRealm
{
public:
    virtual void authenticate(const AuthenticationToken& token) override;
    virtual std::shared_ptr<AuthorizationInfo> authorization(const String& principal) override;
};

}
#endif // GEMINI_DefaultRealm_INCLUDE