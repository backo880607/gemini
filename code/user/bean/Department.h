#ifndef GEMINI_USER_Department_INCLUDE
#define GEMINI_USER_Department_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class GEMINI_USER_API Department : public gemini::EntityObject {
  DECLARE_CLASS(Department, gemini::EntityObject)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Department_INCLUDE