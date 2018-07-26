#ifndef APS_RouteStep_INCLUDE
#define APS_RouteStep_INCLUDE
#include "../../common/Export.h"
#include "../../public/enums/ETech.h"

namespace aps {

class Route;
class RouteStepIn;
class RouteStepOut;
class RouteStepRes;
class StandRouteStep;
class APS_API RouteStep : public gemini::EntityObject {
  DECLARE_CLASS(RouteStep, gemini::EntityObject)

  DECLARE_FIELD(gemini::Int, number)            ///< 工序号
  DECLARE_FIELD(gemini::Double, prevQtyRatio)   ///< 与前工序数量比
  DECLARE_FIELD(gemini::Double, yield)          ///< 成品率
  DECLARE_FIELD(gemini::Double, fixedScrapQty)  ///< 固定报废数
  DECLARE_FIELD(gemini::Boolean, active)        ///< 有效标识
  DECLARE_FIELD(gemini::Double, splitRatio)     ///< 分割比率
  DECLARE_FIELD(gemini::Int, splitQty)          ///< 分割数量
  DECLARE_FIELD(gemini::Double, splitBatch)     ///< 分割批量
  DECLARE_FIELD(gemini::Double, minBatch)       ///< 最小批量
  DECLARE_FIELD(TailDealWay, tailDeal)			///< 尾数处理方式
  DECLARE_FIELD(ContinuousType, contType)       ///< 接续方式
  DECLARE_FIELD(gemini::String, minIntervalCSTR)  ///< 与前工序最小间隔时间
  DECLARE_FIELD(gemini::String, maxIntervalCSTR)  ///< 与前工序最大间隔时间

  DECLARE_ENTITY(Route, route)
  DECLARE_VECTOR(RouteStepIn, routeStepIns)
  DECLARE_VECTOR(RouteStepOut, routeStepOuts)
  DECLARE_VECTOR(RouteStepRes, routeStepReses)
  DECLARE_ENTITY(StandRouteStep, stdRouteStep)
};

}  // namespace aps
#endif  // !APS_RouteStep_INCLUDE