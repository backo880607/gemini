#include "../../../bean/instruction/MaterialCalculation.h"
#include "../../../bean/mstr/Item.h"
#include "../../../bean/order/PlanPurchaseOrder.h"
#include "../../../bean/order/PlanWorkOrder.h"
#include "../../../include/service/instruction/MaterialCalculationServiceImpl.h"

namespace aps {

void MaterialCalculationServiceImpl::execute(
    const gemini::SmartPtr<Instruction>& inst) const {
  MaterialCalculation::SPtr material = inst;
  deleteInvalidPlanOrder();
  std::list<Item::SPtr> items = getList<Item>((gemini::String)material->_itemFilter);
  items.sort([](Item::SPtr lhs, Item::SPtr rhs) {
    gemini::Int result = lhs->_level - rhs->_level;
    return result != 0 ? result : lhs.compare(rhs);
  });
  for (Item::SPtr item : items) {
  }
}

void MaterialCalculationServiceImpl::deleteInvalidPlanOrder() const {
  gemini::IList::Iterator iter = getList<PlanWorkOrder>().iterator();
  while (iter.hasNext()) {
    PlanWorkOrder::SPtr planWorkOrder = iter.next<PlanWorkOrder>();
    if (!planWorkOrder->_active) {
      erase(planWorkOrder);
    }
  }

  iter = getList<PlanPurchaseOrder>().iterator();
  while (iter.hasNext()) {
    PlanPurchaseOrder::SPtr planPurOrder = iter.next<PlanPurchaseOrder>();
    if (!planPurOrder->_active) {
      erase(planPurOrder);
    }
  }
}
}  // namespace aps