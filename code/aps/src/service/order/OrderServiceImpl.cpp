#include "../../../bean/order/Order.h"
#include "../../../bean/plan/Work.h"
#include "../../../include/service/order/OrderServiceImpl.h"
#include "../../../public/service/mstr/ItemService.h"
#include "tools/DoubleUtil.h"

namespace aps {

gemini::ServiceRegister<OrderServiceImpl, OrderService> order_service_register;
gemini::Boolean OrderServiceImpl::isActive(const Order::SPtr& order) const {
  if (!_itemService->isValid(order->_item())) {
    return false;
  }
  if (gemini::DoubleUtil::lessEqual(order->_qty, 0.0)) {
    return false;
  }
  return true;
}

gemini::SmartPtr<Work> OrderServiceImpl::createWork(
    const Order::SPtr& order) const {
  Work::SPtr work = create<Work>();
  work->_order = order;
  return work;
}

}  // namespace aps