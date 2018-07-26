#include "../../../bean/mstr/Item.h"
#include "../../../bean/order/WorkOrder.h"
#include "../../../bean/tech/Route.h"
#include "../../../include/service/order/WorkOrderServiceImpl.h"

namespace aps {

gemini::Boolean WorkOrderServiceImpl::isActive(const Order::SPtr& order) const {
  if (!OrderServiceImpl::isActive(order)) {
    return false;
  }
  Item::SPtr item = order->_item;
  if (item->_type != ItemType::PRODUCT ||
      item->_type != ItemType::HALF_PRODUCT) {
    return false;
  }
  WorkOrder::SPtr workOrder = order;
  if (workOrder->_selectRoute == nullptr) {
    return false;
  }
  return true;
}

gemini::SmartPtr<Route> WorkOrderServiceImpl::selectRoute(
    const gemini::SmartPtr<WorkOrder>& workOrder) const {
  Route::SPtr route;
  return route;
}

}  // namespace aps