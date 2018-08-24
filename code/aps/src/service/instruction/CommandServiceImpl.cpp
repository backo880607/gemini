#include "../../../bean/instruction/CancelTask.h"
#include "../../../bean/instruction/Command.h"
#include "../../../bean/instruction/Instruction.h"
#include "../../../bean/instruction/MaterialCalculation.h"
#include "../../../bean/instruction/PropertyEditor.h"
#include "../../../bean/instruction/WorkLeading.h"
#include "../../../public/service/instruction/InstructionService.h"
#include "../../../include/service/instruction/CommandServiceImpl.h"

namespace aps {

gemini::ServiceRegister<CommandServiceImpl, CommandService>
command_service_register;
gemini::Boolean CommandServiceImpl::execute(
    const gemini::SmartPtr<Command> &entity) const {
  /*foreach_rela<Command::instructs>(entity, [](const Instruction::SPtr& instruct) {
    gemini::ServiceHelper<InstructionService> service(instruct->getClass());
    if (service) {
      service->execute(instruct);
    }
  });*/

  return true;
}

}  // namespace aps