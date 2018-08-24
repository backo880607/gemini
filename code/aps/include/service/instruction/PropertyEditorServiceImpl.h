#ifndef APS_PropertyEditorServiceImpl_INCLUDE
#define APS_PropertyEditorServiceImpl_INCLUDE
#include "../../../public/service/instruction/PropertyEditorService.h"
#include "InstructionServiceImpl.h"

namespace aps {

class PropertyEditorServiceImpl : public InstructionServiceImpl,
                                  public PropertyEditorService {
  virtual void execute(const gemini::SmartPtr<Instruction>& inst) const;
};

}  // namespace aps
#endif  // !APS_PropertyEditorServiceImpl_INCLUDE