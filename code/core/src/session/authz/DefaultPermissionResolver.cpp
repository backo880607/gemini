#include "session/authz/DefaultPermissionResolver.h"
#include "session/authz/DefaultObjectPermission.h"

namespace gemini {
	
std::shared_ptr<ObjectPermission> DefaultPermissionResolver::resolve(const String& permission) const
{
	return std::shared_ptr<ObjectPermission>(new DefaultObjectPermission(permission));
}

}