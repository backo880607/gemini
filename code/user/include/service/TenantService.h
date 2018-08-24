#ifndef GEMINI_USER_TenantService_INCLUDE
#define GEMINI_USER_TenantService_INCLUDE
#include "../../public/service/ITenantService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class TenantService : public BaseService, public ITenantService {};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_TenantService_INCLUDE