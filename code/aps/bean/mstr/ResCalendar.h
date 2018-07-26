#ifndef APS_ResCalendar_INCLUDE
#define APS_ResCalendar_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Shift;
class Resource;
class APS_API ResCalendar : public gemini::EntityObject {
  DECLARE_CLASS(ResCalendar, gemini::EntityObject)

  DECLARE_FIELD(gemini::String, resCode)    ///< 资源代码
  DECLARE_FIELD(gemini::String, date)       ///< 日期
  DECLARE_FIELD(gemini::String, shiftCode)  ///< 班次代码
  DECLARE_FIELD(gemini::Int, priority)      ///< 优先级

  DECLARE_VECTOR(Shift, shifts)
  DECLARE_VECTOR(Resource, reses)
};

}  // namespace aps
#endif  // !APS_ResCalendar_INCLUDE