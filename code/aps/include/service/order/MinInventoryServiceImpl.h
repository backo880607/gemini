#ifndef APS_MinInventoryServiceImpl_INCLUDE
#define APS_MinInventoryServiceImpl_INCLUDE
#include "../../../public/service/order/MinInventoryService.h"
#include "OrderServiceImpl.h"

namespace aps {

class MinInventoryServiceImpl : public OrderServiceImpl,
                                public MinInventoryService {
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
#endif  // APS_MinInventoryServiceImpl_INCLUDE