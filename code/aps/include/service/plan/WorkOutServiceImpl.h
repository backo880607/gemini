#ifndef APS_WorkOutServiceImpl_INCLUDE
#define APS_WorkOutServiceImpl_INCLUDE
#include "../../../public/service/plan/WorkOutService.h"
#include "service/BaseService.h"

namespace aps {

class WorkOutServiceImpl : public gemini::BaseService, WorkOutService {};

}  // namespace aps
#endif  // !APS_WorkOutServiceImpl_INCLUDE