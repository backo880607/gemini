#ifndef APS_Resource_INCLUDE
#define APS_Resource_INCLUDE
#include "..\..\common\Export.h"

namespace aps {

class Task
class APS_API Resource : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(Resource, gemini::EntityObject)
public:
	Resource();
	~Resource();

	DECLARE_FIELD(gemini::String, prevBuffer)
	DECLARE_FIELD(gemini::String, nextBuffer)

	DECLARE_VECTOR(Task, tasks)
};

}
#endif // !APS_Resource_INCLUDE
