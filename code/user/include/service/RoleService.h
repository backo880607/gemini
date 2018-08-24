#ifndef GEMINI_USER_RoleService_INCLUDE
#define GEMINI_USER_RoleService_INCLUDE
#include "../../public/service/IRoleService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class RoleService : public BaseService, public IRoleService {};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_RoleService_INCLUDE