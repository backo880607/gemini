#include "../../../bean/instruction/Instruction.h"
#include "../../../include/service/instruction/InstructionServiceImpl.h"

namespace aps {
gemini::ServiceRegister<InstructionServiceImpl, InstructionService>
    instruction_service_register;
}  // namespace aps