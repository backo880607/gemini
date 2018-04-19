#ifndef APS_StandRouteStep_INCLUDE
#define	APS_StandRouteStep_INCLUDE
#include "../../common/Export.h"
#include "../../public/enums/tech/ScheduleDirection.h"

namespace aps {

class StandRouteStep : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(StandRouteStep, gemini::EntityObject)
public:
	StandRouteStep();
	~StandRouteStep();

	DECLARE_FIELD(ScheduleDirection, direction)
};

}

#endif // APS_StandRouteStep_INCLUDE