#include "session/authz/DefaultObjectPermission.h"
#include "session/authz/DefaultPermissionResolver.h"

namespace gemini {

std::shared_ptr<ObjectPermission> DefaultPermissionResolver::resolve(
    const String& permission) const {
  return std::shared_ptr<ObjectPermission>(
      new DefaultObjectPermission(permission));
}

}  // namespace gemini