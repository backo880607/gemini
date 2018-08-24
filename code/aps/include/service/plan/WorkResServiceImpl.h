#ifndef APS_WorkResServiceImpl_INCLUDE
#define APS_WorkResServiceImpl_INCLUDE
#include "../../../public/service/plan/WorkResService.h"
#include "service/BaseService.h"

namespace aps {

class WorkResServiceImpl : public gemini::BaseService, public WorkResService {};

}  // namespace aps
#endif  // !APS_WorkResServiceImpl_INCLUDE