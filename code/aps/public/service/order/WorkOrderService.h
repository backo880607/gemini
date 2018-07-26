#ifndef APS_WorkOrderService_INCLUDE
#define APS_WorkOrderService_INCLUDE
#include "OrderService.h"

namespace aps {
class Route;
class WorkOrder;
class WorkOrderService : public OrderService {
 public:
  virtual gemini::SmartPtr<Route> selectRoute(
      const gemini::SmartPtr<WorkOrder>& workOrder) const = 0;
};
}  // namespace aps

#endif  // !APS_WorkOrderService_INCLUDE