#ifndef APS_Client_INCLUDE
#define APS_Client_INCLUDE
#include "../../common/Export.h"

namespace aps {

class APS_API Client : public gemini::EntityObject {
  DECLARE_CLASS(Client, gemini::EntityObject)

  DECLARE_FIELD(gemini::String, time)  ///< 工作时间
};

}  // namespace aps
#endif  // APS_Client_INCLUDE