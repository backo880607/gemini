#ifndef APS_WorkLeadingServiceImpl_INCLUDE
#define APS_WorkLeadingServiceImpl_INCLUDE
#include "InstructionServiceImpl.h"
#include "../../../public/service/instruction/WorkLeadingService.h"

namespace aps
{
class WorkLeadingServiceImpl : public InstructionServiceImpl, WorkLeadingService
{
};
} // namespace aps

#endif // !APS_WorkLeadingServiceImpl_INCLUDE