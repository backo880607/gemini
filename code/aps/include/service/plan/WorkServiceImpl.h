#ifndef APS_WorkServiceImpl_INCLUDE
#define APS_WorkServiceImpl_INCLUDE
#include "../../../public/service/plan/WorkService.h"
#include "service/BaseService.h"

namespace aps {

class WorkServiceImpl : public gemini::BaseService, public WorkService {
  virtual void onFree(gemini::BaseEntity::SPtr entity) const;

  virtual gemini::SmartPtr<WorkIn> createWorkIn(
      const gemini::SmartPtr<Work>& work) const;

  virtual gemini::SmartPtr<WorkOut> createWorkOut(
      const gemini::SmartPtr<Work>& work) const;

  virtual gemini::SmartPtr<WorkRes> createWorkRes(
      const gemini::SmartPtr<Work>& work) const;

  virtual gemini::SmartPtr<SingleTask> createSingleTask(
      const gemini::SmartPtr<Work>& work) const;

  virtual gemini::SmartPtr<ToolTask> createToolTask(
      const gemini::SmartPtr<Work>& work) const;

  virtual gemini::SmartPtr<BatchTask> createBatchTask(
      const gemini::SmartPtr<Work>& work) const;
};

}  // namespace aps
#endif  // !APS_WorkServiceImpl_INCLUDE