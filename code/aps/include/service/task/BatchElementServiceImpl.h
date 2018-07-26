#ifndef APS_BatchElementServiceImpl_INCLUDE
#define APS_BatchElementServiceImpl_INCLUDE
#include "../../../public/service/task/BatchElementService.h"
#include "TaskServiceImpl.h"

namespace aps {

class BatchElementServiceImpl : public TaskServiceImpl, BatchElementService {};

}  // namespace aps
#endif  // !APS_BatchElementServiceImpl_INCLUDE