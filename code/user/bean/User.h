#ifndef GEMINI_USER_User_INCLUDE
#define GEMINI_USER_User_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class GEMINI_USER_API User : public gemini::EntityObject {
  DECLARE_CLASS(User, gemini::EntityObject)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_User_INCLUDE