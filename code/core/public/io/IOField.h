#ifndef GEMINI_IO_IOField_INCLUDE
#define GEMINI_IO_IOField_INCLUDE
#include "../Object.h"

namespace gemini {
namespace io {

class IOScheme;
class IOField : public EntityObject
{
	DECLARE_CLASS(IOField, EntityObject)

	DECLARE_FIELD(String, name)
	DECLARE_FIELD(String, externName)
	DECLARE_FIELD(const Field*, field)
	DECLARE_ENTITY(IOScheme, scheme)
};

}
}

#endif // GEMINI_IO_IOField_INCLUDE
