#ifndef APS_CancelTaskServiceImpl_INCLUDE
#define APS_CancelTaskServiceImpl_INCLUDE
#include "../../../public/service/instruction/CancelTaskService.h"
#include "InstructionServiceImpl.h"

namespace aps {

class CancelTaskServiceImpl : public InstructionServiceImpl, public CancelTaskService {
  virtual void execute(const gemini::SmartPtr<Instruction>& inst) const;

  virtual gemini::Boolean cancelTask(const gemini::SmartPtr<Task>& task) const;

  virtual gemini::Boolean cancelWork(const gemini::SmartPtr<Work>& work) const;

  virtual gemini::Boolean cancelOrder(
      const gemini::SmartPtr<Order>& order) const;

  virtual gemini::Boolean cancelResource(
      const gemini::SmartPtr<Resource>& Resource) const;
};

}  // namespace aps
#endif  // !APS_CancelTaskServiceImpl_INCLUDE