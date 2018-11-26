#ifndef GEMINI_USER_DefaultPermissionResolver_INCLUDE
#define GEMINI_USER_DefaultPermissionResolver_INCLUDE
#include "PermissionResolver.h"

namespace gemini {
namespace user {

class DefaultPermissionResolver : public PermissionResolver {
 public:
  virtual std::shared_ptr<ObjectPermission> resolve(
      const String& permission) const override;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DefaultPermissionResolver_INCLUDE