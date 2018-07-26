#ifndef APS_ToolTaskServiceImpl_INCLUDE
#define APS_ToolTaskServiceImpl_INCLUDE
#include "../../../public/service/task/ToolTaskService.h"
#include "TaskServiceImpl.h"

namespace aps {

class ToolTaskServiceImpl : public TaskServiceImpl, ToolTaskService {};

}  // namespace aps
#endif  // !APS_ToolTaskServiceImpl_INCLUDE