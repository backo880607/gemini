#ifndef GEMINI_USER_Department_INCLUDE
#define GEMINI_USER_Department_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class GEMINI_USER_API Department : public gemini::Entity {
  DECLARE_CLASS(Department, gemini::Entity)

  DECLARE_FIELD(String, name)

  DECLARE_ENTITY(Department, parent)
  DECLARE_VECTOR(Department, subordinates)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Department_INCLUDE