#ifndef GEMINI_UsernamePasswordToken_INCLUDE
#define GEMINI_UsernamePasswordToken_INCLUDE
#include "AuthenticationToken.h"

namespace gemini {

class CORE_API UsernamePasswordToken : public AuthenticationToken
{
public:
	UsernamePasswordToken(const String& name, const String& password);
	~UsernamePasswordToken();
};

}
#endif // GEMINI_UsernamePasswordToken_INCLUDE