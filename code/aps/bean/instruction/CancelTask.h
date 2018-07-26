#ifndef APS_CancelTask_INCLUDE
#define APS_CancelTask_INCLUDE
#include "Instruction.h"

namespace aps {

class APS_API CancelTask : public Instruction {
  DECLARE_CLASS(CancelTask, Instruction)

  DECLARE_FIELD(gemini::String, workFilter)
};

}  // namespace aps
#endif  // !APS_CancelTask_INCLUDE