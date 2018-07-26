#ifndef APS_Inventory_INCLUDE
#define APS_Inventory_INCLUDE
#include "Order.h"

namespace aps {

class APS_API Inventory : public Order {
  DECLARE_CLASS(Inventory, Order)

  DECLARE_FIELD(gemini::String, userUpperOrder)
  DECLARE_FIELD(gemini::String, userTopOrder)
  DECLARE_FIELD(gemini::Double, assignedQty)
  DECLARE_FIELD(gemini::Double, surplusQty)
};

}  // namespace aps
#endif  // !APS_Inventory_INCLUDE