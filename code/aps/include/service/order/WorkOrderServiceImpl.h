#ifndef APS_WorkOrderServiceImpl_INCLUDE
#define APS_WorkOrderServiceImpl_INCLUDE
#include "OrderServiceImpl.h"
#include "../../../public/service/order/WorkOrderService.h"

namespace aps
{
class WorkOrderServiceImpl : public OrderServiceImpl, WorkOrderService
{
};
} // namespace aps

#endif // !APS_WorkOrderServiceImpl_INCLUDE