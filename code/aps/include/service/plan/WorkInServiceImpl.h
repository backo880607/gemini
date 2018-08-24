#ifndef APS_WorkInServiceImpl_INCLUDE
#define APS_WorkInServiceImpl_INCLUDE
#include "../../../public/service/plan/WorkInService.h"
#include "service/BaseService.h"

namespace aps {

class WorkInServiceImpl : public gemini::BaseService, public WorkInService {};

}  // namespace aps
#endif  // !APS_WorkInServiceImpl_INCLUDE