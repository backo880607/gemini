#include "../../../bean/task/BatchTask.h"
#include "../../../include/service/task/BatchTaskServiceImpl.h"

namespace aps {
gemini::ServiceRegister<BatchTaskServiceImpl, BatchTaskService>
    batchTask_service_register;
}  // namespace aps