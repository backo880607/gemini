#include "../../../bean/mstr/Item.h"
#include "../../../bean/tech/Route.h"
#include "../../../bean/tech/RouteStep.h"
#include "../../../bean/tech/RouteStepIn.h"
#include "../../../include/service/mstr/ItemServiceImpl.h"

#include <algorithm>

void initAPS() {}
namespace aps {

gemini::ServiceRegister<ItemServiceImpl, ItemService> item_service_register();
gemini::Boolean ItemServiceImpl::calcLevel(const Item::SPtr& item) const {
  if (item->_type == ItemType::SRC_MATERIALS) {
    item->_level = 255;
  } else {
    gemini::Int maxLevel = 0;
    foreach_rela<Item::routeStepIns, RouteStepIn::routeStep, RouteStep::route,
                 Route::item>(item, [&maxLevel](Item::SPtr upItem) {
      maxLevel = std::max((gemini::Int)upItem->_level, maxLevel);
    });
    item->_level = maxLevel;
  }
  return true;
}

gemini::Boolean ItemServiceImpl::isValid(const Item::SPtr& item) const {
  if (item == nullptr) {
    return false;
  }
  if (item->_status != EntityStatus::ENABLE) {
    return false;
  }
  if (!item->_active) {
    return false;
  }

  return true;
}

gemini::SmartPtr<PlanWorkOrder> ItemServiceImpl::createPlanWorkOrder(
    const Item::SPtr& item) const {}

gemini::SmartPtr<PlanPurchaseOrder> ItemServiceImpl::createPlanPurchaseOrder(
    const Item::SPtr& item) const {}

}  // namespace aps