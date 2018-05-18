#ifndef APS_Route_INCLUDE
#define APS_Route_INCLUDE
#include "..\..\common\Export.h"

namespace aps
{
class Item;
class RouteStep;
class APS_API Route : public gemini::EntityObject
{
	DECLARE_CLASS(Route, gemini::EntityObject)

	DECLARE_FIELD(gemini::DateTime, validTimeStart) ///< 有效期间开始时刻
	DECLARE_FIELD(gemini::DateTime, validTimeEnd)   ///< 有效期间结束时刻
	DECLARE_FIELD(gemini::String, condition)		///< 订单适用条件
	DECLARE_FIELD(gemini::Int, priority)			///< 优先级
	DECLARE_FIELD(gemini::Boolean, active)			///< 有效标识

	DECLARE_ENTITY(Item, item)
	DECLARE_VECTOR(RouteStep, routeSteps)
};
} // namespace aps
#endif // !APS_Route_INCLUDE