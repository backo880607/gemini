#ifndef APS_StandRouteStep_INCLUDE
#define APS_StandRouteStep_INCLUDE
#include "../../public/enums/ETech.h"

namespace aps {

class StandRouteStep : public gemini::Entity {
  DECLARE_CLASS(StandRouteStep, gemini::Entity)

  DECLARE_FIELD(TailDealWay, tailDeal)       ///< 尾数处理方式
  DECLARE_FIELD(SchDirection, schDirection)  ///< 排程方向
  DECLARE_FIELD(ResCombLockWay, resCombLock)  ///< 组合资源锁定时间计算方式
  DECLARE_FIELD(ResCombManufWay, resCombManuf)  ///< 组合资源制造时间计算方式
  DECLARE_FIELD(gemini::Int, splitQty)       ///< 按数量分割
  DECLARE_FIELD(gemini::Double, splitBatch)     ///< 按批量分割
  DECLARE_FIELD(gemini::Double, minBatch)       ///< 最小批量
  DECLARE_FIELD(gemini::String, code)        ///< 标准工序代码
  DECLARE_FIELD(gemini::String, name)        ///< 标准工序名称
  DECLARE_FIELD(gemini::String, splitRatio)  ///< 按比例分割
  
};

}  // namespace aps
#endif  // !APS_StandRouteStep_INCLUDE