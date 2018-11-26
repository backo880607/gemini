#ifndef APS_ParentWork_INCLUDE
#define APS_ParentWork_INCLUDE
#include "../../common/Export.h"

namespace aps {

class Order;
class RouteStep;
class Work;
class APS_API ParentWork : public gemini::Entity {
  DECLARE_CLASS(ParentWork, gemini::Entity)

  DECLARE_FIELD(gemini::String, qty)

  DECLARE_ENTITY(Order, order)
  DECLARE_ENTITY(RouteStep, routeStep)
  DECLARE_VECTOR(Work, works)
};

}  // namespace aps
#endif  // !APS_ParentWork_INCLUDE