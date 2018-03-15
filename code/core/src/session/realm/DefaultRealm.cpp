#include "../../../include/session/realm/DefaultRealm.h"
#include "../../../public/session/UsernamePasswordToken.h"
#include "../../../include/session/authz/DefaultAuthorizationInfo.h"
#include "../../../include/session/service/IUserService.h"
#include "../../../include/session/authz/PermissionResolver.h"
#include "../../../public/message/Message.h"
#include "../../../include/session/Errors.h"
#include "../../../include/session/service/UserService.h"

namespace gemini {

void DefaultRealm::authenticate(const AuthenticationToken& token)
{
	const UsernamePasswordToken& userToken = (const UsernamePasswordToken&)token;
	ServiceHelper<IUserService> userService;
	User::SPtr user = userService->login(token.getPrincipal(), token.getCredentials());
	if (!user.valid()) {
		Message::strong_error<AccountError>();
	}
}

std::shared_ptr<AuthorizationInfo> DefaultRealm::authorization(const String& principal)
{
	/*std::shared_ptr<User> user = UserManager::instance().findByUserName(principal);
	if (!user) {
		
	}*/

	std::shared_ptr<AuthorizationInfo> info(new DefaultAuthorizationInfo());

	std::set<String> perms;
	//UserManager::instance().findPermissions(user->_id, perms);

	DefaultAuthorizationInfo* defaultInfo = (DefaultAuthorizationInfo*)info.get();
	for (const String& perm : perms) {
		std::shared_ptr<ObjectPermission> p = getPermissionResolver()->resolve(perm);
		defaultInfo->addObjectPermission(p);
	}

	return info;
}

}