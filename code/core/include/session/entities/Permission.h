#ifndef GEMINI_Permission_INCLUDE
#define GEMINI_Permission_INCLUDE
#include "../../../public/Object.h"

namespace gemini {

class Permission : public EntityObject {
  DECLARE_CLASS(Permission, EntityObject)

  DECLARE_FIELD(String, name)
  DECLARE_FIELD(String, url)
};

}  // namespace gemini
#endif  // GEMINI_Permission_INCLUDE