#ifndef GEMINI_USER_DepartmentService_INCLUDE
#define GEMINI_USER_DepartmentService_INCLUDE
#include "../../public/service/IDepartmentService.h"
#include "service/BaseService.h"

namespace gemini {
namespace user {

class DepartmentService : public BaseService, public IDepartmentService {};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_DepartmentService_INCLUDE