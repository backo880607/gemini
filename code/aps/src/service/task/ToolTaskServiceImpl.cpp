#include "../../../bean/task/ToolTask.h"
#include "../../../include/service/task/ToolTaskServiceImpl.h"

namespace aps {
gemini::ServiceRegister<ToolTaskServiceImpl, ToolTaskService>
    toolTask_service_register;
}  // namespace aps