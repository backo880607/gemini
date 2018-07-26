#ifndef APS_TaskService_INCLUDE
#define APS_TaskService_INCLUDE
#include "service/IBaseService.h"

namespace aps {

class Task;
class TaskService : public gemini::IBaseService {
 public:
  SERVICE_INTERFACE_METHOD(Task, calcBoundaryObverse)
  SERVICE_INTERFACE_METHOD(Task, calcBoundaryReverse)
};

}  // namespace aps
#endif  // APS_TaskService_INCLUDE