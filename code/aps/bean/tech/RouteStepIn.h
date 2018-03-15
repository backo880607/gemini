#ifndef APS_RouteStepIn_INCLUDE
#define APS_RouteStepIn_INCLUDE
#include "..\..\common\Export.h"

namespace aps {

class RouteStep;
class Item;
class APS_API RouteStepIn : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(RouteStepIn, gemini::EntityObject)
public:
	RouteStepIn();
	~RouteStepIn();

	DECLARE_ENTITY(RouteStep, routeStep)
	DECLARE_ENTITY(Item, inputItem)
};

}
#endif // APS_RouteStepIn_INCLUDE