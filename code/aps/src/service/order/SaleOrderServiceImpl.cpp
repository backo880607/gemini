#include "../../../bean/mstr/Item.h"
#include "../../../bean/order/SaleOrder.h"
#include "../../../bean/plan/Work.h"
#include "../../../include/service/order/SaleOrderServiceImpl.h"

namespace aps {

gemini::ServiceRegister<SaleOrderServiceImpl, SaleOrderService>
    saleOrder_service_register;
gemini::Boolean SaleOrderServiceImpl::isActive(const Order::SPtr& order) const {
  if (!OrderServiceImpl::isActive(order)) {
    return false;
  }
  Item::SPtr item = order->_item();
  if (item->_type == ItemType::INTER_PRODUCT ||
      item->_type == ItemType::VIRTUAL) {
    return false;
  }
  return true;
}

gemini::SmartPtr<Work> SaleOrderServiceImpl::createWork(
    const Order::SPtr& order) const {
  Work::SPtr work = OrderServiceImpl::createWork(order);
  return work;
}

}  // namespace aps