#ifndef APS_RouteStepOut_INCLUDE
#define APS_RouteStepOut_INCLUDE
#include "../../common/Export.h"

namespace aps {

class RouteStep;
class Item;
class APS_API RouteStepOut : public gemini::Entity {
  DECLARE_CLASS(RouteStepOut, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)        ///< 有效标识
  DECLARE_FIELD(gemini::Double, outputQty)      ///< 单位产出量
  DECLARE_FIELD(gemini::Double, yield)          ///< 成品率
  DECLARE_FIELD(gemini::Double, fixedScrapQty)  ///< 固定报废数

  DECLARE_ENTITY(RouteStep, routeStep)
  DECLARE_ENTITY(Item, outputItem)
};

}  // namespace aps
#endif  // !APS_RouteStepOut_INCLUDE