#ifndef GEMINI_Authorizer_INCLUDE
#define GEMINI_Authorizer_INCLUDE
#include "../../../public/Common.h"

namespace gemini {

class Authorizer
{
public:
    virtual Boolean isPermitted(const String& principal, const String& permission) = 0;
};

}
#endif // GEMINI_Authorizer_INCLUDE