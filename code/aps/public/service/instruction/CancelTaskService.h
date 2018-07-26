#ifndef APS_CancelTaskService_INCLUDE
#define APS_CancelTaskService_INCLUDE
#include "InstructionService.h"

namespace aps {

class Task;
class Work;
class Order;
class Resource;
class CancelTaskService : public InstructionService {
 public:
  virtual gemini::Boolean cancelTask(
      const gemini::SmartPtr<Task>& task) const = 0;

  virtual gemini::Boolean cancelWork(
      const gemini::SmartPtr<Work>& work) const = 0;

  virtual gemini::Boolean cancelOrder(
      const gemini::SmartPtr<Order>& order) const = 0;

  virtual gemini::Boolean cancelResource(
      const gemini::SmartPtr<Resource>& Resource) const = 0;
};

}  // namespace aps
#endif  // !APS_CancelTaskService_INCLUDE