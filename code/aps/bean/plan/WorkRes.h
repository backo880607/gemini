#ifndef APS_WorkRes_INCLUDE
#define APS_WorkRes_INCLUDE
#include "../../public/enums/ETech.h"

namespace aps {

class Work;
class Resource;
class RouteStepRes;
class APS_API WorkRes : public gemini::Entity {
  DECLARE_CLASS(WorkRes, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)  ///< 有效标识
  DECLARE_FIELD(gemini::Int, priority)    ///< 优先级
  DECLARE_FIELD(UseType, useType)
  DECLARE_FIELD(gemini::String, matchNumber)
  DECLARE_FIELD(gemini::DurationExtend, prevSetTime)  ///< 前设置时间
  DECLARE_FIELD(gemini::DurationExtend, manufTime)    ///< 制造时间
  DECLARE_FIELD(gemini::DurationExtend, nextSetTime)  ///< 后设置时间
  DECLARE_FIELD(gemini::Double, prevSetNeedResQty)  ///< 前设置必要资源量
  DECLARE_FIELD(gemini::Double, manufNeedResQty)    ///< 制造必要资源量
  DECLARE_FIELD(gemini::Double, nextSetNeedResQty)  ///< 后设置必要资源量
  DECLARE_FIELD(gemini::DurationExtend,
                prevSetMaxSdTime)  ///< 最大前设置中断时间
  DECLARE_FIELD(gemini::DurationExtend, manufMaxSdTime)  ///< 最大制造中断时间
  DECLARE_FIELD(gemini::DurationExtend,
                nextSetMaxSdTime)  ///< 最大后设置中断时间

  DECLARE_ENTITY(Work, work)
  DECLARE_ENTITY(Resource, res)
  DECLARE_ENTITY(RouteStepRes, routeStepRes)
};

}  // namespace aps
#endif  // !APS_WorkRes_INCLUDE