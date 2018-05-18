#ifndef APS_Inventory_INCLUDE
#define APS_Inventory_INCLUDE
#include "Order.h"

namespace aps
{
class APS_API Inventory : public Order
{
    DECLARE_CLASS(Inventory, Order)
};
} // namespace aps
#endif // !APS_Inventory_INCLUDE