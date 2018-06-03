#ifndef APS_WorkOut_INCLUDE
#define APS_WorkOut_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class Work;
class WorkRel;
class Item;
class RouteStepOut;
class APS_API WorkOut : public gemini::EntityObject
{
	DECLARE_CLASS(WorkOut, gemini::EntityObject)

	DECLARE_ENTITY(Work, work)
	DECLARE_VECTOR(WorkRel, workRels)
	DECLARE_ENTITY(Item, outputItem)
	DECLARE_ENTITY(RouteStepOut, routeStepOut)
};
} // namespace aps
#endif // !APS_WorkOut_INCLUDE
