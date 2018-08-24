#ifndef APS_InstructionService_INCLUDE
#define APS_InstructionService_INCLUDE
#include "service/IBaseService.h"

namespace aps {

class Instruction;
class InstructionService {
 public:
  virtual void execute(const gemini::SmartPtr<Instruction>& inst) const = 0;
};

}  // namespace aps
#endif  // !APS_InstructionService_INCLUDE