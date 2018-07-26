#ifndef GEMINI_DefaultPermissionResolver_INCLUDE
#define GEMINI_DefaultPermissionResolver_INCLUDE
#include "PermissionResolver.h"

namespace gemini {

class DefaultPermissionResolver : public PermissionResolver {
 public:
  virtual std::shared_ptr<ObjectPermission> resolve(
      const String& permission) const override;
};

}  // namespace gemini
#endif  // GEMINI_DefaultPermissionResolver_INCLUDE