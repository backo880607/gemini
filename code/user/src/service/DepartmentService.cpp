#include "../../include/service/DepartmentService.h"

namespace gemini {
namespace user {
gemini::ServiceRegister<DepartmentService, IDepartmentService>
    department_service_register;
}
}  // namespace gemini