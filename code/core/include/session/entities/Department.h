#ifndef GEMINI_Department_INCLUDE
#define GEMINI_Department_INCLUDE
#include "../../../public/Object.h"

namespace gemini {
    
class Department : public EntityObject
{
    DECLARE_CLASS(Department, EntityObject)

    DECLARE_FIELD(String, name)
	DECLARE_FIELD(String, remark)

    DECLARE_ENTITY(Department, parent)
	DECLARE_VECTOR(Department, childs)
};

}

#endif // !GEMINI_Department_INCLUDE
