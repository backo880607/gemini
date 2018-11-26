#ifndef GEMINI_INTEGRATION_Project_INCLUDE
#define GEMINI_INTEGRATION_Project_INCLUDE
#include "../public/ImportExport.h"
#include "Object.h"

namespace gemini {
namespace integration {

DEFINE_ENUM(SchemeType, Import, Export)

class Scheme;
class GEMINI_INTEGRATION_API Project : public Entity {
  DECLARE_CLASS(Project, Entity)

  DECLARE_FIELD(SchemeType, type)
  DECLARE_FIELD(String, name)

  DECLARE_VECTOR(Scheme, schemes)
};

}  // namespace integration
}  // namespace gemini
#endif  // !GEMINI_INTEGRATION_Project_INCLUDE
