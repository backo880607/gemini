#ifndef APS_MaterialCalculation_INCLUDE
#define APS_MaterialCalculation_INCLUDE
#include "Instruction.h"

namespace aps {

class APS_API MaterialCalculation : public Instruction {
  DECLARE_CLASS(MaterialCalculation, Instruction)

  DECLARE_FIELD(gemini::String, itemFilter)
  DECLARE_FIELD(gemini::String, workInFilter)
  DECLARE_FIELD(gemini::String, workOutFilter)
  DECLARE_FIELD(gemini::Boolean, autoSupply)
  DECLARE_FIELD(gemini::Boolean, keepRel)
  DECLARE_FIELD(gemini::Boolean, batchSupply)
};

}  // namespace aps
#endif  // !APS_MaterialCalculation_INCLUDE