#pragma once
#include "../../../public/service/BaseService.h"
#include "../entities/User.h"
#include "IUserService.h"

namespace gemini {

class IRoleService;
class UserService : public BaseService, public IUserService {
  SERVICE_AUTOWIRED(IRoleService, roleService)
 public:
  virtual User::SPtr login(const String& principal,
                           const String& password) const override;
};

}  // namespace gemini