#ifndef APS_ItemService_INCLUDE
#define APS_ItemService_INCLUDE
#include "service/IBaseService.h"

namespace aps {

class Item;
class PlanWorkOrder;
class PlanPurchaseOrder;
class ItemService : public gemini::IBaseService {
 public:
  SERVICE_INTERFACE_METHOD(Item, calcLevel)

  virtual gemini::Boolean isValid(const gemini::SmartPtr<Item>& item) const = 0;
  virtual gemini::SmartPtr<PlanWorkOrder> createPlanWorkOrder(
      const gemini::SmartPtr<Item>& item) const = 0;
  virtual gemini::SmartPtr<PlanPurchaseOrder> createPlanPurchaseOrder(
      const gemini::SmartPtr<Item>& item) const = 0;
};

}  // namespace aps
#endif  // APS_ItemService_INCLUDE