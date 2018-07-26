#ifndef APS_InventoryServiceImpl_INCLUDE
#define APS_InventoryServiceImpl_INCLUDE
#include "../../../public/service/order/InventoryService.h"
#include "OrderServiceImpl.h"

namespace aps {

class InventoryServiceImpl : public OrderServiceImpl, InventoryService {
  virtual gemini::Boolean isActive(const gemini::SmartPtr<Order>& order) const;
  virtual gemini::SmartPtr<Work> createWork(
      const gemini::SmartPtr<Order>& order) const;
};

}  // namespace aps
#endif  // !APS_InventoryServiceImpl_INCLUDE