#ifndef APS_WorkRes_INCLUDE
#define APS_WorkRes_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class Resource;
class RouteStepRes;
class APS_API WorkRes : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(WorkRes, gemini::EntityObject)
public:
	WorkRes();
	~WorkRes();

	DECLARE_ENTITY(Work, work)
	DECLARE_ENTITY(Resource, res)
	DECLARE_ENTITY(RouteStepRes, routeStepRes)
};

}
#endif // APS_WorkRes_INCLUDE
