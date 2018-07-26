#ifndef APS_Resource_INCLUDE
#define APS_Resource_INCLUDE
#include "../../common/Export.h"
#include "../../public/enums/EMstr.h"

namespace aps {

class Task;
class APS_API Resource : public gemini::EntityObject {
  DECLARE_CLASS(Resource, gemini::EntityObject)

  DECLARE_FIELD(gemini::String, code)                ///< 资源代码
  DECLARE_FIELD(gemini::String, name)                ///< 资源名称
  DECLARE_FIELD(ResCategory, category)               ///< 资源种类
  DECLARE_FIELD(ResType, resType)                    ///< 资源类型
  DECLARE_FIELD(gemini::Boolean, isBottleneck)       ///< 是否为瓶颈资源
  DECLARE_FIELD(gemini::Double, efficiency)          ///< 制造效率
  DECLARE_FIELD(gemini::Double, qtyFactor)           ///< 资源量系数
  DECLARE_FIELD(gemini::Duration, prevBuffer)        ///< 前缓冲时间
  DECLARE_FIELD(gemini::Duration, nextBuffer)        ///< 后缓冲时间
  DECLARE_FIELD(gemini::Double, maxManufBatch)       ///< 最大制造批量
  DECLARE_FIELD(gemini::Duration, lockTime)          ///< 锁定时间
  DECLARE_FIELD(gemini::Duration, prevSetMaxSdTime)  ///< 最大前设置中断时间
  DECLARE_FIELD(gemini::Duration, manufMaxSdTime)  ///< 最大制造中断时间
  DECLARE_FIELD(gemini::Duration, nextSetMaxSdTime)  ///< 最大后设置中断时间
  DECLARE_FIELD(EffectTaskType, manufEffectTask)  ///< 制造效率影响任务类型
  DECLARE_FIELD(EffectTaskType, timeEffectTask)  ///< 时间圆整影响任务类型
  DECLARE_FIELD(EffectTaskType, tailEffectTask)  ///< 时刻尾数圆整影响任务类型
  DECLARE_FIELD(TimeRoundWay, timeRoundWay)  ///< 时间圆整方式

  DECLARE_VECTOR(Task, tasks)
};

}  // namespace aps
#endif  // !APS_Resource_INCLUDE