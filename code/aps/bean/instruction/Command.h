#ifndef APS_Command_INCLUDE
#define APS_Command_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class Instruction;
class APS_API Command : public gemini::EntityObject
{
    DECLARE_CLASS(Command, gemini::EntityObject)

    DECLARE_VECTOR(Instruction, instructs)
};
} // namespace aps

#endif // !APS_Command_INCLUDE