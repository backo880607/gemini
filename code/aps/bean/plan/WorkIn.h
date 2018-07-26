#ifndef APS_WorkIn_INCLUDE
#define APS_WorkIn_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Work;
class WorkRel;
class Item;
class RouteStepIn;
class APS_API WorkIn : public gemini::EntityObject {
  DECLARE_CLASS(WorkIn, gemini::EntityObject)

  DECLARE_FIELD(gemini::Double, lackQty)

  DECLARE_ENTITY(Work, work)
  DECLARE_VECTOR(WorkRel, workRels)
  DECLARE_ENTITY(Item, inputItem)
  DECLARE_ENTITY(RouteStepIn, routeStepIn)
};

}  // namespace aps
#endif  // !APS_WorkIn_INCLUDE