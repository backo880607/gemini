#ifndef APS_ItemServiceImpl_INCLUDE
#define APS_ItemServiceImpl_INCLUDE
#include "../../../public/service/mstr/ItemService.h"
#include "service/BaseService.h"

namespace aps {

class ItemServiceImpl : public gemini::BaseService, public ItemService {
 public:
  //SERVICE_METHOD(Item, calcLevel)
  virtual gemini::Boolean isValid(const gemini::SmartPtr<Item>& item) const;
  virtual gemini::SmartPtr<PlanWorkOrder> createPlanWorkOrder(
      const gemini::SmartPtr<Item>& item) const;
  virtual gemini::SmartPtr<PlanPurchaseOrder> createPlanPurchaseOrder(
      const gemini::SmartPtr<Item>& item) const;

  virtual void test() const override;
};

}  // namespace aps
#endif  // APS_ItemServiceImpl_INCLUDE