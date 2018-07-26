#ifndef GEMINI_IO_IOScheme_INCLUDE
#define GEMINI_IO_IOScheme_INCLUDE
#include "../../public/Object.h"

namespace gemini {
namespace io {

DEFINE_ENUM(IOSchemeType, None, Import, DiffImport, ReplaceImport, Export)

class IOProject;
class IOField;
class CORE_API IOScheme : public EntityObject {
  DECLARE_CLASS(IOScheme, EntityObject)

  DECLARE_FIELD(String, name)
  DECLARE_FIELD(String, conn)
  DECLARE_FIELD(IOSchemeType, type)
  DECLARE_FIELD(String, dataSource)
  DECLARE_FIELD(String, filter)
  DECLARE_FIELD(String, externName)
  DECLARE_FIELD(String, innerName)

  DECLARE_ENTITY(IOProject, project)
  DECLARE_VECTOR(IOField, fields)
};

}  // namespace io
}  // namespace gemini
#endif  // !GEMINI_IO_IOScheme_INCLUDE
