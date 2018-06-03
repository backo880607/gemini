#ifndef APS_WorkRes_INCLUDE
#define APS_WorkRes_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class Work;
class Resource;
class RouteStepRes;
class APS_API WorkRes : public gemini::EntityObject
{
	DECLARE_CLASS(WorkRes, gemini::EntityObject)

	DECLARE_ENTITY(Work, work)
	DECLARE_ENTITY(Resource, res)
	DECLARE_ENTITY(RouteStepRes, routeStepRes)
};
} // namespace aps
#endif // !APS_WorkRes_INCLUDE