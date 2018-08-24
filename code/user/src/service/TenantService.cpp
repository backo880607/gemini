#include "../../include/service/TenantService.h"

namespace gemini {
namespace user {
gemini::ServiceRegister<TenantService, ITenantService> tenant_service_register;
}
}  // namespace gemini