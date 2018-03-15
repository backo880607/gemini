#ifndef GEMINI_AuthorizationInfo_INCLUDE
#define GEMINI_AuthorizationInfo_INCLUDE
#include "ObjectPermission.h"

namespace gemini {

class AuthorizationInfo
{
public:
	virtual const std::vector<std::shared_ptr<ObjectPermission>>& getObjectPermissions() = 0;
};

}
#endif // GEMINI_AuthorizationInfo_INCLUDE