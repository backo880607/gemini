#ifndef GEMINI_USER_AuthorizationInfo_INCLUDE
#define GEMINI_USER_AuthorizationInfo_INCLUDE
#include "ObjectPermission.h"

namespace gemini {
namespace user {

class AuthorizationInfo {
 public:
  virtual const std::vector<std::shared_ptr<ObjectPermission>>&
  getObjectPermissions() = 0;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_AuthorizationInfo_INCLUDE