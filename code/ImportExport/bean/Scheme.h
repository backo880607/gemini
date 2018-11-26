#ifndef GEMINI_INTEGRATION_Scheme_INCLUDE
#define GEMINI_INTEGRATION_Scheme_INCLUDE
#include "../public/ImportExport.h"
#include "Object.h"

namespace gemini {
namespace integration {

DEFINE_ENUM(ImportType, None, ReplaceImport, DiffImport, TimestampImport)

class Project;
class FieldInfo;
class Source;
class GEMINI_INTEGRATION_API Scheme : public Entity {
  DECLARE_CLASS(Scheme, Entity)

  DECLARE_FIELD(String, name)
  DECLARE_FIELD(ImportType, importType)
  DECLARE_FIELD(String, filter)
  DECLARE_FIELD(String, orderBy)
  DECLARE_FIELD(String, externName)
  DECLARE_FIELD(String, innerName)

  DECLARE_ENTITY(Project, project)
  DECLARE_ENTITY(Source, source)
  DECLARE_VECTOR(FieldInfo, fields)
};

}  // namespace integration
}  // namespace gemini
#endif  // !GEMINI_INTEGRATION_Scheme_INCLUDE
