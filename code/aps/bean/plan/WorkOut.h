#ifndef APS_WorkOut_INCLUDE
#define APS_WorkOut_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class WorkRel;
class Item;
class RouteStepOut;
class APS_API WorkOut : public gemini::Entity {
  DECLARE_CLASS(WorkOut, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)     ///< �Ƿ���Ч
  DECLARE_FIELD(gemini::Double, qty)         ///< ����
  DECLARE_FIELD(gemini::Double, surplusQty)  ///< ��������
  DECLARE_FIELD(gemini::DateTime, time)      ///< ʱ��

  DECLARE_ENTITY(Work, work)
  DECLARE_VECTOR(WorkRel, workRels)
  DECLARE_ENTITY(Item, outputItem)
  DECLARE_ENTITY(RouteStepOut, routeStepOut)
};

}  // namespace aps
#endif  // !APS_WorkOut_INCLUDE
