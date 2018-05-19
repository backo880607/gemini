#ifndef APS_ToolTaskServiceImpl_INCLUDE
#define APS_ToolTaskServiceImpl_INCLUDE
#include "TaskServiceImpl.h"
#include "../../../public/service/task/ToolTaskService.h"

namespace aps
{
class ToolTaskServiceImpl : public TaskServiceImpl, ToolTaskService
{
};
} // namespace aps

#endif // !APS_ToolTaskServiceImpl_INCLUDE