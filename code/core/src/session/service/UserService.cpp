#include "../../../include/session/service/UserService.h"

namespace gemini {

ServiceRegister<UserService, IUserService> user_service_register;
User::SPtr UserService::login(const String & principal, const String & password) const
{
	User::SPtr user(true);
	return user;
}

}