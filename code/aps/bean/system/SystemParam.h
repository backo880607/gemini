#ifndef APS_SystemParam_INCLUDE
#define APS_SystemParam_INCLUDE
#include "../../common/Export.h"

namespace aps {

class APS_API SystemParam : public gemini::BaseEntity {
  DECLARE_CLASS(SystemParam, gemini::BaseEntity)

  DECLARE_FIELD(gemini::DateTime, baseTime)
};

}  // namespace aps
#endif  // !APS_SystemParam_INCLUDE