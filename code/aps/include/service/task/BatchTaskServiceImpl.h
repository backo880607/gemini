#ifndef APS_BatchTaskServiceImpl_INCLUDE
#define APS_BatchTaskServiceImpl_INCLUDE
#include "../../../public/service/task/BatchTaskService.h"
#include "TaskServiceImpl.h"

namespace aps {

class BatchTaskServiceImpl : public TaskServiceImpl, public BatchTaskService {
 public:
  virtual gemini::Boolean calcBoundaryObverse(
      const gemini::SmartPtr<Task> &entity) const override {
    return true;
  }
  virtual gemini::Boolean calcBoundaryReverse(
      const gemini::SmartPtr<Task> &entity) const override {
    return true;
  }
};

}  // namespace aps
#endif  // !APS_BatchTaskServiceImpl_INCLUDE