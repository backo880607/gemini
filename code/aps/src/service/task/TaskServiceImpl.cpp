#include "../../../include/service/task/TaskServiceImpl.h"

namespace aps {
    
gemini::ServiceRegister<TaskServiceImpl, TaskService> task_service_register();
gemini::Boolean TaskService::calcBoundaryObverse(const gemini::SmartPtr<Task>& entity) const
{

}

gemini::Boolean TaskService::calcBoundaryReverse(const gemini::SmartPtr<Task>& entity) const
{

}

}