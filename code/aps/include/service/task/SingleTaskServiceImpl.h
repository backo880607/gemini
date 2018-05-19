#ifndef APS_SingleTaskServiceImpl_INCLUDE
#define APS_SingleTaskServiceImpl_INCLUDE
#include "TaskServiceImpl.h"
#include "../../../public/service/task/SingleTaskService.h"

namespace aps
{
class SingleTaskServiceImpl : public TaskServiceImpl, SingleTaskService
{
};
} // namespace aps

#endif // !APS_SingleTaskServiceImpl_INCLUDE