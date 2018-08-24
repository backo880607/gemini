#include "../../../bean/instruction/WorkLeading.h"
#include "../../../include/service/instruction/WorkLeadingServiceImpl.h"

namespace aps {

gemini::ServiceRegister<WorkLeadingServiceImpl, WorkLeadingService>
    workLeading_service_register;
void WorkLeadingServiceImpl::execute(
    const gemini::SmartPtr<Instruction>& inst) const {}

}  // namespace aps