#ifndef APS_BatchElementServiceImpl_INCLUDE
#define APS_BatchElementServiceImpl_INCLUDE
#include "../../../public/service/task/BatchElementService.h"
#include "TaskServiceImpl.h"

namespace aps {

class BatchElementServiceImpl : public TaskServiceImpl, public BatchElementService {
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
#endif  // !APS_BatchElementServiceImpl_INCLUDE