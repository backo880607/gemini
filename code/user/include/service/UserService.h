#ifndef GEMINI_USER_UserService_INCLUDE
#define GEMINI_USER_UserService_INCLUDE
#include "../../public/service/IUserService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class UserService : public BaseService, public IUserService {};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_UserService_INCLUDE