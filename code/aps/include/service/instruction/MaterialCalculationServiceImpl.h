#ifndef APS_MaterialCalculationServiceImpl_INCLUDE
#define APS_MaterialCalculationServiceImpl_INCLUDE
#include "../../../public/service/instruction/MaterialCalculationService.h"
#include "InstructionServiceImpl.h"

namespace aps {

class MaterialCalculationServiceImpl : public InstructionServiceImpl,
                                       MaterialCalculationService {
  virtual void execute(const gemini::SmartPtr<Instruction>& inst) const;
  void deleteInvalidPlanOrder() const;
};

}  // namespace aps
#endif  // !APS_MaterialCalculationServiceImpl_INCLUDE