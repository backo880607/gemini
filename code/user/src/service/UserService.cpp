#include "../../include/service/UserService.h"

namespace gemini {
namespace user {
gemini::ServiceRegister<UserService, IUserService> user_service_register;
}
}  // namespace gemini