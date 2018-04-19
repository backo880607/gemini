#ifndef APS_TaskServiceImpl_INCLUDE
#define APS_TaskServiceImpl_INCLUDE
#include "../../../public/service/task/TaskService.h"
#include "service/BaseService.h"

namespace aps {
    
class TaskServiceImpl : public gemini::BaseService, TaskService
{
public:
	SERVICE_METHOD(Task, calcBoundaryObverse)
	SERVICE_METHOD(Task, calcBoundaryReverse)
};

}
#endif // APS_TaskServiceImpl_INCLUDE
#define 