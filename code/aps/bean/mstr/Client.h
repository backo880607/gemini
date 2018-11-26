#ifndef APS_Client_INCLUDE
#define APS_Client_INCLUDE
#include "../../common/Export.h"

namespace aps {

class APS_API Client : public gemini::Entity {
  DECLARE_CLASS(Client, gemini::Entity)

  DECLARE_FIELD(gemini::String, name)  ///< 名称
};

}  // namespace aps
#endif  // APS_Client_INCLUDE