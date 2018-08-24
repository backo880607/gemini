#ifndef APS_WorkOrderServiceImpl_INCLUDE
#define APS_WorkOrderServiceImpl_INCLUDE
#include "../../../public/service/order/WorkOrderService.h"
#include "OrderServiceImpl.h"

namespace aps {

class WorkOrderServiceImpl : public OrderServiceImpl, public WorkOrderService {
  virtual gemini::Boolean isActive(const gemini::SmartPtr<Order>& order) const;
  virtual gemini::SmartPtr<Route> selectRoute(
      const gemini::SmartPtr<WorkOrder>& workOrder) const;

  virtual gemini::SmartPtr<Work> createWork(
      const gemini::SmartPtr<Order>& order) const {
    return nullptr;
  }
};

}  // namespace aps
#endif  // !APS_WorkOrderServiceImpl_INCLUDE