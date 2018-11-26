#ifndef GEMINI_USER_UserService_INCLUDE
#define GEMINI_USER_UserService_INCLUDE
#include "../../public/service/IUserService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class IRoleService;
class UserService : public BaseService, public IUserService {
  SERVICE_AUTOWIRED(IRoleService, roleService)
 public:
  virtual User::SPtr login(const String& principal,
                           const String& password) const override;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_UserService_INCLUDE