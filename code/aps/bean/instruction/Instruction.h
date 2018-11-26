#ifndef APS_Instruction_INCLUDE
#define APS_Instruction_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Command;
class APS_API Instruction : public gemini::Entity {
  DECLARE_CLASS(Instruction, gemini::Entity)

  DECLARE_ENTITY(Command, command)
};

}  // namespace aps
#endif  // !APS_Instruction_INCLUDE