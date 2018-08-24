#ifndef APS_SafeInventoryServiceImpl_INCLUDE
#define APS_SafeInventoryServiceImpl_INCLUDE
#include "../../../public/service/order/SafeInventoryService.h"
#include "OrderServiceImpl.h"

namespace aps {

class SafeInventoryServiceImpl : public OrderServiceImpl,
                                 public SafeInventoryService {
 public:
  virtual gemini::Boolean isActive(const gemini::SmartPtr<Order>& order) const {
    return true;
  }

  virtual gemini::SmartPtr<Work> createWork(
      const gemini::SmartPtr<Order>& order) const {
    return nullptr;
  }
};

}  // namespace aps
#endif  // APS_SafeInventoryServiceImpl_INCLUDE