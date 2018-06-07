#ifndef GEMINI_IO_IOProject_INCLUDE
#define GEMINI_IO_IOProject_INCLUDE
#include "../Object.h"

namespace gemini {
namespace io {

class IOScheme;
class IOProject : public EntityObject
{
	DECLARE_CLASS(IOProject, EntityObject)

	DECLARE_FIELD(String, name)
	DECLARE_VECTOR(IOScheme, schemes)
};

}
}

#endif // GEMINI_IO_IOProject_INCLUDE
