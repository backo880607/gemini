#ifndef APS_BatchTaskServiceImpl_INCLUDE
#define APS_BatchTaskServiceImpl_INCLUDE
#include "TaskServiceImpl.h"
#include "../../../public/service/task/BatchTaskService.h"

namespace aps
{
class BatchTaskServiceImpl : public TaskServiceImpl, BatchTaskService
{
};
} // namespace aps

#endif // !APS_BatchTaskServiceImpl_INCLUDE