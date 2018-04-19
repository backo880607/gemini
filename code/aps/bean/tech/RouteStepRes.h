#pragma once
#include "..\..\common\Export.h"

namespace aps {

class RouteStep;
class APS_API RouteStepRes : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(RouteStepRes, gemini::EntityObject)
public:
	RouteStepRes();
	~RouteStepRes();

	DECLARE_ENTITY(RouteStep, routeStep)
	DECLARE_ENTITY(Resource, res)
};

}