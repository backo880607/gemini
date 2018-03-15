#pragma once
#include "..\..\common\Export.h"

namespace aps {

class StandRouteStep : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(StandRouteStep, gemini::EntityObject)
public:
	StandRouteStep();
	~StandRouteStep();
};

}