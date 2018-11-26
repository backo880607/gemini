#ifndef GEMINI_INTEGRATION_FieldInfo_INCLUDE
#define GEMINI_INTEGRATION_FieldInfo_INCLUDE
#include "../public/ImportExport.h"
#include "Object.h"

namespace gemini {
namespace integration {

class Scheme;
class GEMINI_INTEGRATION_API FieldInfo : public Entity {
  DECLARE_CLASS(FieldInfo, Entity)

  DECLARE_FIELD(Boolean, primary)
  DECLARE_FIELD(String, name)
  DECLARE_FIELD(String, externName)
  const Field* _field;

  DECLARE_ENTITY(Scheme, scheme)
};

}  // namespace integration
}  // namespace gemini
#endif  // !GEMINI_INTEGRATION_FieldInfo_INCLUDE