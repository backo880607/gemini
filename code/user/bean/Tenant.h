#ifndef GEMINI_USER_Tenant_INCLUDE
#define GEMINI_USER_Tenant_INCLUDE
#include "../public/UserExport.h"
#include "Object.h"

namespace gemini {
namespace user {

class GEMINI_USER_API Tenant : public gemini::Entity {
  DECLARE_CLASS(Tenant, gemini::Entity)

  DECLARE_FIELD(String, name)
  DECLARE_FIELD(String, phone)
  DECLARE_FIELD(String, fax)
  DECLARE_FIELD(String, address)
  DECLARE_FIELD(String, email)
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Tenant_INCLUDE