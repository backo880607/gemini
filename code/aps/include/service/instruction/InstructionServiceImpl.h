#ifndef APS_InstructionServiceImpl_INCLUDE
#define APS_InstructionServiceImpl_INCLUDE
#include "../../../public/service/instruction/InstructionService.h"
#include "service/BaseService.h"

namespace aps {

class InstructionServiceImpl : public gemini::BaseService,
                               InstructionService {};

}  // namespace aps
#endif  // !APS_InstructionServiceImpl_INCLUDE