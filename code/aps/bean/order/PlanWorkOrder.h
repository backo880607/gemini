#ifndef APS_PlanWorkOrder_INCLUDE
#define APS_PlanWorkOrder_INCLUDE
#include "WorkOrder.h"

namespace aps {

class Route;
class APS_API PlanWorkOrder : public WorkOrder {
  DECLARE_CLASS(PlanWorkOrder, Order)
};

}  // namespace aps
#endif  // !APS_PlanWorkOrder_INCLUDE