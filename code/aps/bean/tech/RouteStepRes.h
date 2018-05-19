#ifndef APS_RouteStepRes_INCLUDE
#define APS_RouteStepRes_INCLUDE
#include "../../common/Export.h"

namespace aps
{
class RouteStep;
class APS_API RouteStepRes : public gemini::EntityObject
{
	DECLARE_CLASS(RouteStepRes, gemini::EntityObject)

	DECLARE_FIELD(gemini::String, prevSetTime)		 ///< 前设置时间
	DECLARE_FIELD(gemini::String, manufTime)		 ///< 制造时间
	DECLARE_FIELD(gemini::String, postSetTime)		 ///< 后设置时间
	DECLARE_FIELD(gemini::Double, prevSetNeedResQty) ///< 前设置必要资源量
	DECLARE_FIELD(gemini::Double, manufNeedResQty)   ///< 制造必要资源量
	DECLARE_FIELD(gemini::Double, postSetNeedResQty) ///< 后设置必要资源量
	DECLARE_FIELD(gemini::String, prevSetMaxSdTime)  ///< 最大前设置中断时间
	DECLARE_FIELD(gemini::String, manufMaxSdTime)	///< 最大制造中断时间
	DECLARE_FIELD(gemini::String, postSetMaxSdTime)  ///< 最大后设置中断时间
	DECLARE_FIELD(gemini::Int, priority)			 ///< 优先级
	DECLARE_FIELD(gemini::Boolean, active)			 ///< 有效标识

	DECLARE_ENTITY(RouteStep, routeStep)
	DECLARE_ENTITY(Resource, res)
};

} // namespace aps

#endif // !APS_RouteStepRes_INCLUDE