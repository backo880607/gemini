#ifndef APS_TransTime_INCLUDE
#define APS_TransTime_INCLUDE
#include "../../common/Export.h"

namespace aps {

class APS_API TransTime : public gemini::Entity {
  DECLARE_CLASS(TransTime, gemini::Entity)

  DECLARE_FIELD(gemini::Int, priority)        ///< 优先级
  DECLARE_FIELD(gemini::String, prevSopCode)  ///< 前标准工序代码
  DECLARE_FIELD(gemini::String, nextSopCode)  ///< 后标准工序代码
  DECLARE_FIELD(gemini::String, prevResCode)  ///< 前资源代码
  DECLARE_FIELD(gemini::String, nextResCode)  ///< 后资源代码
  DECLARE_FIELD(gemini::String, time)         ///< 时间
};

}  // namespace aps
#endif  // !APS_TransTime_INCLUDE