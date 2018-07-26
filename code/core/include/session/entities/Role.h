#ifndef GEMINI_Role_INCLUDE
#define GEMINI_Role_INCLUDE
#include "../../../public/Object.h"

namespace gemini {

class Role : public EntityObject {
  DECLARE_CLASS(Role, EntityObject)

  DECLARE_FIELD(String, name)
  DECLARE_FIELD(String, remark)

  DECLARE_ENTITY(Role, parent)
  DECLARE_VECTOR(Role, childs)
};

}  // namespace gemini
#endif  // GEMINI_Role_INCLUDE