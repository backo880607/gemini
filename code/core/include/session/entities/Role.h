#ifndef GEMINI_Role_INCLUDE
#define GEMINI_Role_INCLUDE
#include "../../../public/Object.h"

namespace gemini {

class Role : public EntityObject
{
	DECLARE_CLASS(Role, EntityObject)

	DECLARE_FIELD(String, name)
	DECLARE_FIELD(String, remark)
};

}
#endif // GEMINI_Role_INCLUDE