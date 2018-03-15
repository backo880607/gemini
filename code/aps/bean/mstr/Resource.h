#ifndef APS_Resource_INCLUDE
#define APS_Resource_INCLUDE
#include "..\..\common\Export.h"

namespace aps {

class APS_API Resource : public gemini::EntityObject
{
	DECLARE_CLASS(Resource, gemini::EntityObject)
public:
	Resource();
	~Resource();
};

}
#endif // !APS_Resource_INCLUDE
