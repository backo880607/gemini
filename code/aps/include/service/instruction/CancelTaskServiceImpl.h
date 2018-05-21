#ifndef APS_CancelTaskServiceImpl_INCLUDE
#define APS_CancelTaskServiceImpl_INCLUDE
#include "InstructionServiceImpl.h"
#include "../../../public/service/instruction/CancelTaskService.h"

namespace aps
{
class CancelTaskServiceImpl : public InstructionServiceImpl, CancelTaskService
{
};
} // namespace aps

#endif // !APS_CancelTaskServiceImpl_INCLUDE