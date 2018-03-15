#pragma once
#include "..\..\common\Export.h"

namespace aps {

class Route;
class RouteStepIn;
class RouteStepOut;
class RouteStepRes;
class StandRouteStep;
class APS_API RouteStep : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(RouteStep, gemini::EntityObject)
public:
	RouteStep();
	~RouteStep();

	DECLARE_ENTITY(Route, route)
	DECLARE_VECTOR(RouteStepIn, routeStepIns)
	DECLARE_VECTOR(RouteStepOut, routeStepOuts)
	DECLARE_VECTOR(RouteStepRes, routeStepReses)
	DECLARE_ENTITY(StandRouteStep, stdRouteStep)
};

}