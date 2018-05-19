#ifndef APS_PurchaseOrderServiceImpl_INCLUDE
#define APS_PurchaseOrderServiceImpl_INCLUDE
#include "OrderServiceImpl.h"
#include "../../../public/service/order/PurchaseOrderService.h"

namespace aps
{
class PurchaseOrderServiceImpl : public OrderServiceImpl, PurchaseOrderService
{
};
} // namespace aps

#endif // !APS_PurchaseOrderServiceImpl_INCLUDE