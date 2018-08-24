#include "../../../bean/instruction/PropertyEditor.h"
#include "../../../include/service/instruction/PropertyEditorServiceImpl.h"

namespace aps {

gemini::ServiceRegister<PropertyEditorServiceImpl, PropertyEditorService>
    propertyEditor_service_register;
void PropertyEditorServiceImpl::execute(
    const gemini::SmartPtr<Instruction>& inst) const {}

}  // namespace aps