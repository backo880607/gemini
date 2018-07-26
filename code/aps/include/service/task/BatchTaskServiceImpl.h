#ifndef APS_BatchTaskServiceImpl_INCLUDE
#define APS_BatchTaskServiceImpl_INCLUDE
#include "../../../public/service/task/BatchTaskService.h"
#include "TaskServiceImpl.h"

namespace aps {

class BatchTaskServiceImpl : public TaskServiceImpl, BatchTaskService {};

}  // namespace aps
#endif  // !APS_BatchTaskServiceImpl_INCLUDE