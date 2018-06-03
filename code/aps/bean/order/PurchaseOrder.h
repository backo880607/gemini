#ifndef APS_PurchaseOrder_INCLUDE
#define APS_PurchaseOrder_INCLUDE
#include "Order.h"

namespace aps
{
class APS_API PurchaseOrder : public Order
{
    DECLARE_CLASS(PurchaseOrder, Order)
};
} // namespace aps
#endif // !APS_PurchaseOrder_INCLUDE