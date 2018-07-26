#ifndef APS_WorkService_INCLUDE
#define APS_WorkService_INCLUDE
#include "service/IBaseService.h"

namespace aps {

class Work;
class WorkIn;
class WorkOut;
class WorkRes;
class SingleTask;
class ToolTask;
class BatchTask;
class WorkService : public gemini::IBaseService {
 public:
  virtual gemini::SmartPtr<WorkIn> createWorkIn(
      const gemini::SmartPtr<Work>& work) const = 0;

  virtual gemini::SmartPtr<WorkOut> createWorkOut(
      const gemini::SmartPtr<Work>& work) const = 0;

  virtual gemini::SmartPtr<WorkRes> createWorkRes(
      const gemini::SmartPtr<Work>& work) const = 0;

  virtual gemini::SmartPtr<SingleTask> createSingleTask(
      const gemini::SmartPtr<Work>& work) const = 0;

  virtual gemini::SmartPtr<ToolTask> createToolTask(
      const gemini::SmartPtr<Work>& work) const = 0;

  virtual gemini::SmartPtr<BatchTask> createBatchTask(
      const gemini::SmartPtr<Work>& work) const = 0;
};

}  // namespace aps
#endif  // !APS_WorkService_INCLUDE