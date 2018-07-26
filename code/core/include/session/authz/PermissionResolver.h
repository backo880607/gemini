#ifndef GEMINI_PermissionResolver_INCLUDE
#define GEMINI_PermissionResolver_INCLUDE
#include "ObjectPermission.h"

namespace gemini {

class PermissionResolver {
 public:
  virtual ~PermissionResolver() {}
  virtual std::shared_ptr<ObjectPermission> resolve(
      const String& permission) const = 0;
};

}  // namespace gemini
#endif  // GEMINI_PermissionResolver_INCLUDE