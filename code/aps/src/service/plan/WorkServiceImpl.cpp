#include "../../../bean/plan/Work.h"
#include "../../../bean/plan/WorkIn.h"
#include "../../../bean/plan/WorkOut.h"
#include "../../../bean/plan/WorkRes.h"
#include "../../../bean/task/BatchTask.h"
#include "../../../bean/task/SingleTask.h"
#include "../../../bean/task/ToolTask.h"
#include "../../../include/service/plan/WorkServiceImpl.h"

namespace aps {

gemini::ServiceRegister<WorkServiceImpl, WorkService> work_service_register;
void WorkServiceImpl::onFree(gemini::EntityObject::SPtr entity) const {}

gemini::SmartPtr<WorkIn> WorkServiceImpl::createWorkIn(
    const Work::SPtr& work) const {
  WorkIn::SPtr workIn = create<WorkIn>();
  return workIn;
}

gemini::SmartPtr<WorkOut> WorkServiceImpl::createWorkOut(
    const Work::SPtr& work) const {
  WorkOut::SPtr workOut = create<WorkOut>();
  return workOut;
}

gemini::SmartPtr<WorkRes> WorkServiceImpl::createWorkRes(
    const Work::SPtr& work) const {
  WorkRes::SPtr workRes = create<WorkRes>();
  return workRes;
}

gemini::SmartPtr<SingleTask> WorkServiceImpl::createSingleTask(
    const Work::SPtr& work) const {
  SingleTask::SPtr singleTask = create<SingleTask>();
  return singleTask;
}

gemini::SmartPtr<ToolTask> WorkServiceImpl::createToolTask(
    const Work::SPtr& work) const {
  ToolTask::SPtr toolTask = create<ToolTask>();
  return toolTask;
}

gemini::SmartPtr<BatchTask> WorkServiceImpl::createBatchTask(
    const Work::SPtr& work) const {
  BatchTask::SPtr batchTask = create<BatchTask>();
  return batchTask;
}

}  // namespace aps
