#ifndef APS_TaskServiceImpl_INCLUDE
#define APS_TaskServiceImpl_INCLUDE
#include "../../../public/service/task/TaskService.h"
#include "service/BaseService.h"

namespace aps {

class TaskServiceImpl : public gemini::BaseService, public TaskService {
 public:
  SERVICE_METHOD(Task, calcBoundaryObverse)
  SERVICE_METHOD(Task, calcBoundaryReverse)
};

}  // namespace aps
#endif  // APS_TaskServiceImpl_INCLUDE