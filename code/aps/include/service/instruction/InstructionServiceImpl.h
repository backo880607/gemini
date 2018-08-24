#ifndef APS_InstructionServiceImpl_INCLUDE
#define APS_InstructionServiceImpl_INCLUDE
#include "../../../public/service/instruction/InstructionService.h"
#include "service/BaseService.h"

namespace aps {

class InstructionServiceImpl : public gemini::BaseService,
                               public InstructionService {
 public:
  virtual void execute(const gemini::SmartPtr<Instruction>& inst) const {}
};

}  // namespace aps
#endif  // !APS_InstructionServiceImpl_INCLUDE