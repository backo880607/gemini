#ifndef APS_OrderServiceImpl_INCLUDE
#define APS_OrderServiceImpl_INCLUDE
#include "../../../public/service/order/OrderService.h"
#include "service/BaseService.h"

namespace aps {

class ItemService;
class OrderServiceImpl : public gemini::BaseService, OrderService {
  SERVICE_AUTOWIRED(ItemService, itemService)

  virtual gemini::Boolean isActive(const gemini::SmartPtr<Order>& order) const;

  virtual gemini::SmartPtr<Work> createWork(
      const gemini::SmartPtr<Order>& order) const;
};

}  // namespace aps
#endif  // !APS_OrderServiceImpl_INCLUDE