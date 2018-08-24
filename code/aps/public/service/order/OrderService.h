#ifndef APS_OrderService_INCLUDE
#define APS_OrderService_INCLUDE
#include "service/IBaseService.h"

namespace aps {

class Order;
class Work;
class OrderService {
 public:
  virtual gemini::Boolean isActive(
      const gemini::SmartPtr<Order>& order) const = 0;

  virtual gemini::SmartPtr<Work> createWork(
      const gemini::SmartPtr<Order>& order) const = 0;
};

}  // namespace aps
#endif  // !APS_OrderService_INCLUDE