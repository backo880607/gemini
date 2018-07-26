#ifndef APS_SaleOrder_INCLUDE
#define APS_SaleOrder_INCLUDE
#include "Order.h"

namespace aps {

class Client;
class APS_API SaleOrder : public Order {
  DECLARE_CLASS(SaleOrder, Order)

  DECLARE_FIELD(gemini::DateTime, userLET)
  DECLARE_FIELD(gemini::DateTime, lowerEST)
  DECLARE_FIELD(gemini::DateTime, userLowerEST)
  DECLARE_FIELD(gemini::DateTime, userLeadTime)
  DECLARE_FIELD(gemini::DateTime, calcLeadTime)

  DECLARE_ENTITY(Client, client);
};

}  // namespace aps
#endif  // !APS_SaleOrder_INCLUDE