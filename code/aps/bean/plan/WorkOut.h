#ifndef APS_WorkOut_INCLUDE
#define APS_WorkOut_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class APS_API WorkOut : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(WorkOut, gemini::EntityObject)

public:
	WorkOut();
	~WorkOut();

	DECLARE_ENTITY(Work, work)
	DECLARE_VECTOR(WorkRel, workRels)
	DECLARE_ENTITY(Item, outputItem)
	DECLARE_ENTITY(RouteStepOut, routeStepOut)
};

}
#endif // !APS_WorkOut_INCLUDE
