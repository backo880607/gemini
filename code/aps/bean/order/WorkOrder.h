#ifndef APS_WorkOrder_INCLUDE
#define APS_WorkOrder_INCLUDE
#include "Order.h"

namespace aps {

class Route;
class APS_API WorkOrder : public Order {
  DECLARE_CLASS(WorkOrder, Order)

  DECLARE_FIELD(gemini::Double, assignedQty)
  DECLARE_FIELD(gemini::Double, surplusQty)
  DECLARE_FIELD(gemini::DateTime, est)
  DECLARE_FIELD(gemini::DateTime, userEST)
  DECLARE_FIELD(gemini::DateTime, userLET)
  DECLARE_FIELD(gemini::DateTime, lowerEST)
  DECLARE_FIELD(gemini::DateTime, userLowerEST)
  DECLARE_FIELD(gemini::DateTime, userLeadTime)
  DECLARE_FIELD(gemini::DateTime, calcLeadTime)
  DECLARE_FIELD(gemini::String, userRoute)
  DECLARE_FIELD(gemini::String, userUpperOrder)
  DECLARE_FIELD(gemini::String, userTopOrder)

  DECLARE_ENTITY(Route, selectRoute)
};

}  // namespace aps
#endif  // !APS_WorkOrder_INCLUDE