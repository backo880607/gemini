#include "../../include/service/RoleService.h"

namespace gemini {
namespace user {
gemini::ServiceRegister<RoleService, IRoleService> role_service_register;
}
}  // namespace gemini