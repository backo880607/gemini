#pragma once
#include "..\..\common\Export.h"

namespace aps {

class Item;
class RouteStep;
class APS_API Route : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(Route, gemini::EntityObject)
public:
	Route();
	~Route();

	DECLARE_ENTITY(Item, item)
	DECLARE_VECTOR(RouteStep, routeSteps)
};
}