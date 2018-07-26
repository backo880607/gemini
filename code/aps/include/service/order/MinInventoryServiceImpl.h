#ifndef APS_MinInventoryServiceImpl_INCLUDE
#define APS_MinInventoryServiceImpl_INCLUDE
#include "../../../public/service/order/MinInventoryService.h"
#include "OrderServiceImpl.h"

namespace aps {

class MinInventoryServiceImpl : public OrderServiceImpl, MinInventoryService {
  virtual gemini::Boolean isActive(const gemini::SmartPtr<Order>& order) const;
};

}  // namespace aps
#endif  // APS_MinInventoryServiceImpl_INCLUDE