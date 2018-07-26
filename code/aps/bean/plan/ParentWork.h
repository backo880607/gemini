#ifndef APS_ParentWork_INCLUDE
#define APS_ParentWork_INCLUDE
#include "../../common/Export.h"

namespace aps {
class Order;
class RouteStep;
class APS_API ParentWork : public gemini::EntityObject {
  DECLARE_CLASS(ParentWork, gemini::EntityObject)

  DECLARE_FIELD(gemini::String, qty)

  DECLARE_ENTITY(Order, order)
  DECLARE_ENTITY(RouteStep, routeStep)
};
}  // namespace aps
#endif  // !APS_ParentWork_INCLUDE