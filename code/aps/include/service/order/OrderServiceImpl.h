#ifndef APS_OrderServiceImpl_INCLUDE
#define APS_OrderServiceImpl_INCLUDE
#include "../../../public/service/order/OrderService.h"
#include "service/BaseService.h"

namespace aps
{
class OrderServiceImpl : public gemini::BaseService, OrderService
{
};
} // namespace aps

#endif // !APS_OrderServiceImpl_INCLUDE