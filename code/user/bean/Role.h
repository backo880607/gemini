#ifndef GEMINI_USER_Role_INCLUDE
#define GEMINI_USER_Role_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class GEMINI_USER_API Role : public gemini::EntityObject {
  DECLARE_CLASS(Role, gemini::EntityObject)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Role_INCLUDE