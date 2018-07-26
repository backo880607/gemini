#ifndef APS_PurchaseOrder_INCLUDE
#define APS_PurchaseOrder_INCLUDE
#include "Order.h"

namespace aps {

class APS_API PurchaseOrder : public Order {
  DECLARE_CLASS(PurchaseOrder, Order)

  DECLARE_FIELD(gemini::String, userUpperOrder)
  DECLARE_FIELD(gemini::String, userTopOrder)
  DECLARE_FIELD(gemini::Double, assignedQty)
  DECLARE_FIELD(gemini::Double, surplusQty)
  DECLARE_FIELD(gemini::DateTime, userLeadTime)
  DECLARE_FIELD(gemini::DateTime, calcLeadTime)
};

}  // namespace aps
#endif  // !APS_PurchaseOrder_INCLUDE