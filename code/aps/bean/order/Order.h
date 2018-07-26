#ifndef APS_Order_INCLUDE
#define APS_Order_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class Item;
class APS_API Order : public gemini::EntityObject {
  DECLARE_CLASS(Order, gemini::EntityObject)

  DECLARE_FIELD(gemini::String, code)   ///< 订单代码
  DECLARE_FIELD(gemini::Double, qty)    ///< 数量
  DECLARE_FIELD(gemini::Int, priority)  ///< 优先级
  DECLARE_FIELD(gemini::DateTime, let)  ///< 最晚结束时刻
  DECLARE_FIELD(gemini::DateTime, estCalc)
  DECLARE_FIELD(gemini::DateTime, letCalc)
  DECLARE_FIELD(gemini::DateTime, planStart)
  DECLARE_FIELD(gemini::DateTime, planEnd)
  DECLARE_FIELD(gemini::Boolean, active)
  DECLARE_FIELD(gemini::DateTime, receiveDate)

  DECLARE_ENTITY(Item, item)  ///< 物品
  DECLARE_VECTOR(Work, works)
  DECLARE_VECTOR(Order, upperOrders)
  DECLARE_VECTOR(Order, lowerOrders)
};

}  // namespace aps
#endif  // !APS_Order_INCLUDE