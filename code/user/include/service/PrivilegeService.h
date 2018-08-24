#ifndef GEMINI_USER_PrivilegeService_INCLUDE
#define GEMINI_USER_PrivilegeService_INCLUDE
#include "../../public/service/IPrivilegeService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class PrivilegeService : public BaseService, public IPrivilegeService {};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_PrivilegeService_INCLUDE