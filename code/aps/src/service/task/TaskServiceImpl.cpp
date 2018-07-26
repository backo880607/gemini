#include "../../../bean/task/Task.h"
#include "../../../include/service/task/TaskServiceImpl.h"

namespace aps {

gemini::ServiceRegister<TaskServiceImpl, TaskService> task_service_register();
gemini::Boolean TaskServiceImpl::calcBoundaryObverse(
    const gemini::SmartPtr<Task> &entity) const {}

gemini::Boolean TaskServiceImpl::calcBoundaryReverse(
    const gemini::SmartPtr<Task> &entity) const {}

}  // namespace aps