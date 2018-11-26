#ifndef APS_Order_INCLUDE
#define APS_Order_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class Item;
class APS_API Order : public gemini::Entity {
  DECLARE_CLASS(Order, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)
  DECLARE_FIELD(gemini::Int, priority)          ///< 优先级
  DECLARE_FIELD(gemini::Double, qty)            ///< 数量
  DECLARE_FIELD(gemini::DateTime, let)          ///< 最晚结束时刻
  DECLARE_FIELD(gemini::DateTime, estCalc)      ///< 最早开始日期计算值
  DECLARE_FIELD(gemini::DateTime, letCalc)      ///< 最晚结束日期计算值
  DECLARE_FIELD(gemini::DateTime, planStart)    ///< 计划开始时刻
  DECLARE_FIELD(gemini::DateTime, planEnd)      ///< 计划结束时刻
  DECLARE_FIELD(gemini::DateTime, receiveDate)  ///< 接单时间
  DECLARE_FIELD(gemini::String, code)           ///< 订单代码
  DECLARE_FIELD(gemini::String, name)           ///< 订单名称
  DECLARE_FIELD(gemini::String, specifiedGroup)  ///< 专用料分组号

  DECLARE_ENTITY(Item, item)  ///< 物品
  DECLARE_VECTOR(Work, works)
  DECLARE_VECTOR(Order, upperOrders)
  DECLARE_VECTOR(Order, lowerOrders)
};

}  // namespace aps
#endif  // !APS_Order_INCLUDE