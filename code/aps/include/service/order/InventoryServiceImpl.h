#ifndef APS_InventoryServiceImpl_INCLUDE
#define APS_InventoryServiceImpl_INCLUDE
#include "OrderServiceImpl.h"
#include "../../../public/service/order/InventoryService.h"

namespace aps
{
class InventoryServiceImpl : public OrderServiceImpl, InventoryService
{
};
} // namespace aps

#endif // !APS_InventoryServiceImpl_INCLUDE