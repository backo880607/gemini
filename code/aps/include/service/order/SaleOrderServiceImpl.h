#ifndef APS_SaleOrderServiceImpl_INCLUDE
#define APS_SaleOrderServiceImpl_INCLUDE
#include "../../../public/service/order/SaleOrderService.h"
#include "OrderServiceImpl.h"

namespace aps {

class SaleOrderServiceImpl : public OrderServiceImpl, SaleOrderService {
  virtual gemini::Boolean isActive(const gemini::SmartPtr<Order>& order) const;
  virtual gemini::SmartPtr<Work> createWork(
      const gemini::SmartPtr<Order>& order) const;
};

}  // namespace aps
#endif  // !APS_SaleOrderServiceImpl_INCLUDE