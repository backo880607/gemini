#ifndef GEMINI_USER_Privilege_INCLUDE
#define GEMINI_USER_Privilege_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class GEMINI_USER_API Privilege : public gemini::EntityObject {
  DECLARE_CLASS(Privilege, gemini::EntityObject)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Privilege_INCLUDE