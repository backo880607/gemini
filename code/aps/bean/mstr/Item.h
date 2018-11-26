#ifndef APS_Item_INCLUDE
#define APS_Item_INCLUDE
#include "../../public/enums/ECommon.h"
#include "../../public/enums/EMstr.h"

namespace aps {

class Order;
class Route;
class RouteStepIn;
class RouteStepOut;
class APS_API Item : public gemini::Entity {
  DECLARE_CLASS(Item, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)            ///< 有效标识
  DECLARE_FIELD(gemini::Boolean, isFdbkRecursion)   ///< 是否实绩递归
  DECLARE_FIELD(gemini::Boolean, isAutoFixPegging)  ///< 自动固定关联
  DECLARE_FIELD(ItemType, type)                     ///< 物品种类
  DECLARE_FIELD(EntityStatus, status)
  DECLARE_FIELD(ItemPrepareWay, prepareWay)         ///< 备料方式
  DECLARE_FIELD(SupplyWay, supplyWay)               ///< 自动补充标识
  DECLARE_FIELD(gemini::Int, level)                 ///< 低阶码
  DECLARE_FIELD(gemini::Int, priority)              ///< 优先级
  DECLARE_FIELD(gemini::Int, unitPur)               ///< 单位采购量
  DECLARE_FIELD(gemini::Int, unitManuf)             ///< 单位制造量
  DECLARE_FIELD(gemini::Int, unitShipments)         ///< 单位配送量
  DECLARE_FIELD(gemini::Double, maxManufBatch)      ///< 最大制造批量
  DECLARE_FIELD(gemini::Double, minManufBatch)      ///< 最小制造批量
  DECLARE_FIELD(gemini::Double, manufBatchUnit)     ///< 制造批量单位
  DECLARE_FIELD(gemini::Double, maxPurBatch)        ///< 最大采购批量
  DECLARE_FIELD(gemini::Double, minPurBatch)        ///< 最小采购批量
  DECLARE_FIELD(gemini::Double, purBatchUnit)       ///< 采购批量单位
  DECLARE_FIELD(gemini::Double, minStockQty)        ///< 最小库存量
  DECLARE_FIELD(gemini::Double, safeStockQty)       ///< 安全库存量
  DECLARE_FIELD(gemini::Double, maxStockQty)        ///< 最高库存量
  DECLARE_FIELD(gemini::String, code)               ///< 物品代码
  DECLARE_FIELD(gemini::String, name)               ///< 物品名称
  DECLARE_FIELD(gemini::String, purLT)              ///< 固定采购提前期
  DECLARE_FIELD(gemini::String, manufLT)            ///< 固定制造提前期
  DECLARE_FIELD(gemini::String, shipmentLT)         ///< 固定配送提前期
  DECLARE_FIELD(gemini::String, orderMergePeriod)   ///< 订单合并期间

  DECLARE_VECTOR(Order, orders)
  DECLARE_VECTOR(Route, routes)
  DECLARE_VECTOR(RouteStepIn, routeStepIns)
  DECLARE_VECTOR(RouteStepOut, routeStepOuts)
};

}  // namespace aps
#endif  // !APS_Item_INCLUDE