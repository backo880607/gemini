#ifndef GEMINI_USER_DefaultAuthorizationInfo_INCLUDE
#define GEMINI_USER_DefaultAuthorizationInfo_INCLUDE
#include "AuthorizationInfo.h"

namespace gemini {
namespace user {

class DefaultAuthorizationInfo : public AuthorizationInfo {
 public:
  virtual const std::vector<std::shared_ptr<ObjectPermission>>&
  getObjectPermissions() override {
    return m_permissions;
  }
  void addObjectPermission(const std::shared_ptr<ObjectPermission>& value) {
    m_permissions.push_back(value);
  }

 private:
  std::vector<std::shared_ptr<ObjectPermission>> m_permissions;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DefaultAuthorizationInfo_INCLUDE