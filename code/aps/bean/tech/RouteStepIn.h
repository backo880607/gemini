#ifndef APS_RouteStepIn_INCLUDE
#define APS_RouteStepIn_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class RouteStep;
class Item;
class APS_API RouteStepIn : public gemini::EntityObject
{
	DECLARE_CLASS(RouteStepIn, gemini::EntityObject)

	DECLARE_FIELD(gemini::Double, inputQty)		   ///< 单位投料量
	DECLARE_FIELD(gemini::Double, yield)		   ///< 成品率
	DECLARE_FIELD(gemini::Double, fixedScrapQty)   ///< 固定报废数
	DECLARE_FIELD(gemini::String, minIntervalCSTR) ///< 与前工序最小间隔时间
	DECLARE_FIELD(gemini::String, maxIntervalCSTR) ///< 与前工序最大间隔时间
	DECLARE_FIELD(gemini::Boolean, active)		   ///< 有效标识

	DECLARE_ENTITY(RouteStep, routeStep)
	DECLARE_ENTITY(Item, inputItem)
};
} // namespace aps

#endif // !APS_RouteStepIn_INCLUDE