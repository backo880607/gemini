#include "../../../bean/mstr/Item.h"
#include "../../../bean/order/PurchaseOrder.h"
#include "../../../include/service/order/PurchaseOrderServiceImpl.h"

namespace aps {

gemini::Boolean PurchaseOrderServiceImpl::isActive(
    const Order::SPtr& order) const {
  if (!OrderServiceImpl::isActive(order)) {
    return false;
  }
  Item::SPtr item = order->_item;
  if (item->_type == ItemType::INTER_PRODUCT ||
      item->_type == ItemType::VIRTUAL) {
    return false;
  }
  return true;
}

}  // namespace aps