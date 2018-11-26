#ifndef GEMINI_USER_PermissionResolver_INCLUDE
#define GEMINI_USER_PermissionResolver_INCLUDE
#include "ObjectPermission.h"

namespace gemini {
namespace user {

class PermissionResolver {
 public:
  virtual ~PermissionResolver() {}
  virtual std::shared_ptr<ObjectPermission> resolve(
      const String& permission) const = 0;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_PermissionResolver_INCLUDE