#include "../../../bean/task/SingleTask.h"
#include "../../../include/service/task/SingleTaskServiceImpl.h"

namespace aps {
gemini::ServiceRegister<SingleTaskServiceImpl, SingleTaskService>
    singleTask_service_register;
}  // namespace aps