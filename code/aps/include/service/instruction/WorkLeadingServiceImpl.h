#ifndef APS_WorkLeadingServiceImpl_INCLUDE
#define APS_WorkLeadingServiceImpl_INCLUDE
#include "../../../public/service/instruction/WorkLeadingService.h"
#include "InstructionServiceImpl.h"

namespace aps {

class WorkLeadingServiceImpl : public InstructionServiceImpl,
                               WorkLeadingService {
  virtual void execute(const gemini::SmartPtr<Instruction>& inst) const;
};

}  // namespace aps
#endif  // !APS_WorkLeadingServiceImpl_INCLUDE