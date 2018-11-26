#ifndef GEMINI_INTEGRATION_Source_INCLUDE
#define GEMINI_INTEGRATION_Source_INCLUDE
#include "../public/ImportExport.h"
#include "Object.h"

namespace gemini {
namespace integration {

class GEMINI_INTEGRATION_API Source : public Entity {
  DECLARE_CLASS(Source, Entity)

  DECLARE_FIELD(String, name)
};

class GEMINI_INTEGRATION_API ExcelCSVSource : public Source {
  DECLARE_CLASS(ExcelCSVSource, Source)
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_Source_INCLUDE