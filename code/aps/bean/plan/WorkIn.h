#ifndef APS_WorkIn_INCLUDE
#define APS_WorkIn_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class WorkRel;
class Item;
class RouteStepIn;
class APS_API WorkIn : public gemini::Entity {
  DECLARE_CLASS(WorkIn, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)  ///< 是否有效
  DECLARE_FIELD(gemini::Double, qty)      ///< 数量
  DECLARE_FIELD(gemini::Double, lackQty)  ///< 不足数量
  DECLARE_FIELD(gemini::DateTime, time)   ///< 物品需求时刻

  DECLARE_ENTITY(Work, work)
  DECLARE_VECTOR(WorkRel, workRels)
  DECLARE_ENTITY(Item, inputItem)
  DECLARE_ENTITY(RouteStepIn, routeStepIn)
};

}  // namespace aps
#endif  // !APS_WorkIn_INCLUDE