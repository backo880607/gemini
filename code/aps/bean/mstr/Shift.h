#ifndef APS_Shift_INCLUDE
#define APS_Shift_INCLUDE
#include "../../common/Export.h"

namespace aps {

class APS_API Shift : public gemini::Entity {
  DECLARE_CLASS(Shift, gemini::Entity)

  DECLARE_FIELD(gemini::String, time)  ///< 工作时间
};

}  // namespace aps
#endif  // !APS_Shift_INCLUDE