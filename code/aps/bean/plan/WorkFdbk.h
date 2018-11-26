#ifndef APS_WorkFdbk_INCLUDE
#define APS_WorkFdbk_INCLUDE
#include "../../public/enums/EPlan.h"

namespace aps {

class Work;
class APS_API WorkFdbk : public gemini::Entity {
  DECLARE_CLASS(WorkFdbk, gemini::Entity)

  DECLARE_FIELD(PlanStatus, fdbkStatus)
  DECLARE_FIELD(gemini::Double, qty)
  DECLARE_FIELD(gemini::Double, incrementQty)
  DECLARE_FIELD(gemini::Double, progress)
  DECLARE_FIELD(gemini::DateTime, start)
  DECLARE_FIELD(gemini::DateTime, end)
  DECLARE_FIELD(gemini::DateTime, obtainTime)
  DECLARE_FIELD(gemini::String, res)

  DECLARE_ENTITY(Work, work)
};

}  // namespace aps
#endif  // !APS_WorkFdbk_INCLUDE