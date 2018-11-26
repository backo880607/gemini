#include "../../../bean/plan/WorkIn.h"
#include "../../../bean/plan/WorkOut.h"
#include "../../../bean/plan/WorkRel.h"
#include "../../../include/service/plan/WorkRelServiceImpl.h"

namespace aps {

gemini::ServiceRegister<WorkRelServiceImpl, WorkRelService>
    workRel_service_register;
void WorkRelServiceImpl::onFree(gemini::BaseEntity::SPtr entity) const {
  WorkRel::SPtr workRel = entity;
  WorkIn::SPtr workIn = getRela<WorkRel::workIn>(entity);
  WorkOut::SPtr workOut = getRela<WorkRel::workOut>(entity);
  if (workIn.valid() && workOut.valid()) {
    workIn->_lackQty = workIn->_lackQty + workRel->_qty;
    workOut->_surplusQty = workOut->_surplusQty + workRel->_qty;
  }
}

}  // namespace aps