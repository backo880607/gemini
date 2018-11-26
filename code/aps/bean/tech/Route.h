/*
 * @Author: haitao.niu
 * @Date: 2018-05-22 22:39:29
 * @Last Modified by:   haitao.niu
 * @Last Modified time: 2018-05-22 22:39:29
 */
#ifndef APS_Route_INCLUDE
#define APS_Route_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Item;
class RouteStep;
class APS_API Route : public gemini::Entity {
  DECLARE_CLASS(Route, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)           ///< 有效标识
  DECLARE_FIELD(gemini::Int, priority)             ///< 优先级
  DECLARE_FIELD(gemini::DateTime, validTimeStart)  ///< 有效期间开始时刻
  DECLARE_FIELD(gemini::DateTime, validTimeEnd)    ///< 有效期间结束时刻
  DECLARE_FIELD(gemini::String, code)              ///< 工艺路径代码
  DECLARE_FIELD(gemini::String, name)              ///< 工艺路径名称
  DECLARE_FIELD(gemini::String, condition)         ///< 订单适用条件

  DECLARE_ENTITY(Item, item)
  DECLARE_VECTOR(RouteStep, routeSteps)
};

}  // namespace aps
#endif  // !APS_Route_INCLUDE