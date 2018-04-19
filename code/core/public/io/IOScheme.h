#ifndef GEMINI_IO_IOScheme_INCLUDE
#define GEMINI_IO_IOScheme_INCLUDE
#include "../Object.h"

namespace gemini {
namespace io {

class IOProject;
class IOField;
class CORE_API IOScheme : public EntityObject
{
#define MODULE_API
	DECLARE_CLASS(IOScheme, EntityObject)

	enum class Type {
		None,
		Import,
		DiffImport,
		ReplaceImport,
		Export
	};

	DECLARE_FIELD(String, name)
	DECLARE_FIELD(String, conn)
	DECLARE_FIELD(IOScheme::Type, type)
	DECLARE_FIELD(String, filter)
	DECLARE_FIELD(String, externName)
	DECLARE_FIELD(String, innerName)

	DECLARE_ENTITY(IOProject, project)
	DECLARE_VECTOR(IOField, fields)
};

}
}
#endif // GEMINI_IO_IOScheme_INCLUDE
