#ifndef APS_WorkInServiceImpl_INCLUDE
#define APS_WorkInServiceImpl_INCLUDE
#include "../../../public/service/plan/WorkService.h"
#include "service/BaseService.h"

namespace aps
{
class WorkServiceImpl : public gemini::BaseService, WorkService
{
};
} // namespace aps
#endif // !APS_WorkInServiceImpl_INCLUDE