#ifndef APS_MaterialCalculationServiceImpl_INCLUDE
#define APS_MaterialCalculationServiceImpl_INCLUDE
#include "InstructionServiceImpl.h"
#include "../../../public/service/instruction/MaterialCalculationService.h"

namespace aps
{
class MaterialCalculationServiceImpl : public InstructionServiceImpl, MaterialCalculationService
{
};
} // namespace aps

#endif // !APS_MaterialCalculationServiceImpl_INCLUDE