#ifndef APS_ToolTaskServiceImpl_INCLUDE
#define APS_ToolTaskServiceImpl_INCLUDE
#include "../../../public/service/task/ToolTaskService.h"
#include "TaskServiceImpl.h"

namespace aps {

class ToolTaskServiceImpl : public TaskServiceImpl, public ToolTaskService {
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
#endif  // !APS_ToolTaskServiceImpl_INCLUDE