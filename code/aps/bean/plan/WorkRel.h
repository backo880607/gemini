#ifndef APS_WorkRel_INCLUDE
#define APS_WorkRel_INCLUDE
#include "../../public/enums/EPlan.h"
#include "../../public/enums/ETech.h"

namespace aps {

class Item;
class Work;
class WorkIn;
class WorkOut;
class APS_API WorkRel : public gemini::Entity {
  DECLARE_CLASS(WorkRel, gemini::Entity)

  DECLARE_FIELD(gemini::Boolean, active)
  DECLARE_FIELD(gemini::Boolean, isRelaFixed)
  DECLARE_FIELD(gemini::Boolean, isQtyFixed)
  DECLARE_FIELD(gemini::Double, qty)
  DECLARE_FIELD(WorkRelType, relaType)
  DECLARE_FIELD(ContinuousType, contType)
  DECLARE_FIELD(gemini::DurationExtend, minTimeCSTR)
  DECLARE_FIELD(gemini::DurationExtend, maxTimeCSTR)

  DECLARE_ENTITY(Item, item)
  DECLARE_ENTITY(Work, prevWork)
  DECLARE_ENTITY(Work, nextWork)
  DECLARE_ENTITY(WorkIn, workIn)
  DECLARE_ENTITY(WorkOut, workOut)
};

}  // namespace aps
#endif  // !APS_WorkRel_INCLUDE