#ifndef GEMINI_PermissionResolver_INCLUDE
#define GEMINI_PermissionResolver_INCLUDE
#include "ObjectPermission.h"

namespace gemini {

class PermissionResolver
{
public:
	virtual std::shared_ptr<ObjectPermission> resolve(const String& permission) const = 0;

};

}
#endif // GEMINI_PermissionResolver_INCLUDE