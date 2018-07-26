#include "../../../bean/instruction/CancelTask.h"
#include "../../../bean/plan/Work.h"
#include "../../../include/service/instruction/CancelTaskServiceImpl.h"

namespace aps {

void CancelTaskServiceImpl::execute(
    const gemini::SmartPtr<Instruction>& inst) const {
  CancelTask::SPtr cancelTask = inst;
  std::list<Work::SPtr> works =
      getList<Work>(((const gemini::String&)cancelTask->_workFilter).c_str());
  for (Work::SPtr work : works) {
  }
}

gemini::Boolean CancelTaskServiceImpl::cancelTask(
    const gemini::SmartPtr<Task>& task) const {
  return true;
}

gemini::Boolean CancelTaskServiceImpl::cancelWork(
    const gemini::SmartPtr<Work>& work) const {
  return true;
}

gemini::Boolean CancelTaskServiceImpl::cancelOrder(
    const gemini::SmartPtr<Order>& order) const {
  return true;
}

gemini::Boolean CancelTaskServiceImpl::cancelResource(
    const gemini::SmartPtr<Resource>& Resource) const {
  return true;
}

}  // namespace aps