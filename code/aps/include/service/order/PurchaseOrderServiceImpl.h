#ifndef APS_PurchaseOrderServiceImpl_INCLUDE
#define APS_PurchaseOrderServiceImpl_INCLUDE
#include "../../../public/service/order/PurchaseOrderService.h"
#include "OrderServiceImpl.h"

namespace aps {

class PurchaseOrderServiceImpl : public OrderServiceImpl, PurchaseOrderService {
  virtual gemini::Boolean isActive(const gemini::SmartPtr<Order>& order) const;
  virtual gemini::SmartPtr<Work> createWork(
      const gemini::SmartPtr<Order>& order) const;
};

}  // namespace aps
#endif  // !APS_PurchaseOrderServiceImpl_INCLUDE