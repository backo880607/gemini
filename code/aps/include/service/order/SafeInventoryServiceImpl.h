#ifndef APS_SafeInventoryServiceImpl_INCLUDE
#define APS_SafeInventoryServiceImpl_INCLUDE
#include "../../../public/service/order/SafeInventoryService.h"
#include "OrderServiceImpl.h"

namespace aps {

class SafeInventoryServiceImpl : public OrderServiceImpl, SafeInventoryService {
  virtual gemini::Boolean isActive(const gemini::SmartPtr<Order>& order) const;
};

}  // namespace aps
#endif  // APS_SafeInventoryServiceImpl_INCLUDE