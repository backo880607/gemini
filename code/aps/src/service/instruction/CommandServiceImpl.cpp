#include "../../../include/service/instruction/CommandServiceImpl.h"
#include "../../../bean/instruction/Command.h"
#include "../../../bean/instruction/Instruction.h"

namespace aps
{
gemini::ServiceRegister<CommandServiceImpl, CommandService> task_service_register();
gemini::Boolean CommandServiceImpl::execute(const gemini::SmartPtr<Command> &entity) const
{
    foreach
        <Instruction, Command::instructs>(entity, [](Instruction::SPtr instruct) {
        });
}
} // namespace aps