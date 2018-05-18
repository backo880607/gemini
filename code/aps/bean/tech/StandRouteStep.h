#ifndef APS_StandRouteStep_INCLUDE
#define APS_StandRouteStep_INCLUDE
#include "../../common/Export.h"
#include "../../public/enums/tech/ScheduleDirection.h"

namespace aps
{
class StandRouteStep : public gemini::EntityObject
{
	DECLARE_CLASS(StandRouteStep, gemini::EntityObject)

	DECLARE_FIELD(gemini::String, splitRatio) ///< 按比例分割
	DECLARE_FIELD(gemini::Int, splitQty)	  ///< 按数量分割
	DECLARE_FIELD(gemini::Double, splitBatch) ///< 按批量分割
	DECLARE_FIELD(gemini::Double, minBatch)   ///< 最小批量

	DECLARE_FIELD(ScheduleDirection, direction)
};
} // namespace aps
#endif // !APS_StandRouteStep_INCLUDE