#ifndef GEMINI_USER_Tenant_INCLUDE
#define GEMINI_USER_Tenant_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class GEMINI_USER_API Tenant : public gemini::EntityObject {
  DECLARE_CLASS(Tenant, gemini::EntityObject)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Tenant_INCLUDE