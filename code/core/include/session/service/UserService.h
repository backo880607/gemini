#pragma once
#include "IUserService.h"
#include "../../../public/service/BaseService.h"
#include "../entities/User.h"

namespace gemini {

class IRoleService;
class UserService : public BaseService, public IUserService
{
	SERVICE_AUTOWIRED(IRoleService, roleService)
public:
	virtual User::SPtr login(const String& principal, const String& password) const override;
};

}