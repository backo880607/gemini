#ifndef APS_SingleTaskServiceImpl_INCLUDE
#define APS_SingleTaskServiceImpl_INCLUDE
#include "../../../public/service/task/SingleTaskService.h"
#include "TaskServiceImpl.h"

namespace aps {

class SingleTaskServiceImpl : public TaskServiceImpl, SingleTaskService {};

}  // namespace aps
#endif  // !APS_SingleTaskServiceImpl_INCLUDE