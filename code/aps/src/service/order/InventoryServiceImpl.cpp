#include "../../../bean/mstr/Item.h"
#include "../../../bean/order/Inventory.h"
#include "../../../include/service/order/InventoryServiceImpl.h"

namespace aps {

gemini::Boolean InventoryServiceImpl::isActive(const Order::SPtr& order) const {
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