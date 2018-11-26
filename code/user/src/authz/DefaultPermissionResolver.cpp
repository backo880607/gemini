#include "../../include/authz/DefaultObjectPermission.h"
#include "../../include/authz/DefaultPermissionResolver.h"

namespace gemini {
namespace user {

std::shared_ptr<ObjectPermission> DefaultPermissionResolver::resolve(
    const String& permission) const {
  return std::shared_ptr<ObjectPermission>(
      new DefaultObjectPermission(permission));
}

}  // namespace user
}  // namespace gemini