#ifndef APS_WorkRel_INCLUDE
#define APS_WorkRel_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class WorkIn;
class WorkOut;
class APS_API WorkRel : public gemini::EntityObject {
  DECLARE_CLASS(WorkRel, gemini::EntityObject)

  DECLARE_FIELD(gemini::Double, qty)
  // DECLARE_FIELD(ContinuousType, contType)
  DECLARE_FIELD(gemini::String, minTimeCSTR)
  DECLARE_FIELD(gemini::String, maxTimeCSTR)

  DECLARE_ENTITY(Work, prevWork)
  DECLARE_ENTITY(Work, nextWork)
  DECLARE_ENTITY(WorkIn, workIn)
  DECLARE_ENTITY(WorkOut, workOut)
};

}  // namespace aps
#endif  // !APS_WorkRel_INCLUDE