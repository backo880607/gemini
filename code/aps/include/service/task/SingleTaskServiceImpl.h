#ifndef APS_SingleTaskServiceImpl_INCLUDE
#define APS_SingleTaskServiceImpl_INCLUDE
#include "../../../public/service/task/SingleTaskService.h"
#include "TaskServiceImpl.h"

namespace aps {

class SingleTaskServiceImpl : public TaskServiceImpl, public SingleTaskService {
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
#endif  // !APS_SingleTaskServiceImpl_INCLUDE