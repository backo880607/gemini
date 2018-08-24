#include "../../include/service/PrivilegeService.h"

namespace gemini {
namespace user {
gemini::ServiceRegister<PrivilegeService, IPrivilegeService>
    privilege_service_register;
}
}  // namespace gemini