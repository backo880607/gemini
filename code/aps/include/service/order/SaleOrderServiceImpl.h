#ifndef APS_SaleOrderServiceImpl_INCLUDE
#define APS_SaleOrderServiceImpl_INCLUDE
#include "OrderServiceImpl.h"
#include "../../../public/service/order/SaleOrderService.h"

namespace aps
{
class SaleOrderServiceImpl : public OrderServiceImpl, SaleOrderService
{
};
} // namespace aps

#endif // !APS_SaleOrderServiceImpl_INCLUDE