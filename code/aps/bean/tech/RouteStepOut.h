#pragma once
#include "..\..\common\Export.h"

namespace aps {

class RouteStep;
class APS_API RouteStepOut : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(RouteStepOut, gemini::EntityObject)
public:
	RouteStepOut();
	~RouteStepOut();

	DECLARE_ENTITY(RouteStep, routeStep)
	DECLARE_ENTITY(Item, outputItem)
};

}