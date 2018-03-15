#ifndef GEMINI_Realm_INCLUDE
#define GEMINI_Realm_INCLUDE
#include "../../../public/Common.h"

namespace gemini {

class AuthenticationToken;
class Realm
{
public:
    Boolean supports(const AuthenticationToken& token);
    virtual void authenticate(const AuthenticationToken& token) = 0;
};

}
#endif // GEMINI_Realm_INCLUDE