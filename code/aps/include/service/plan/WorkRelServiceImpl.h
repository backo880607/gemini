#ifndef APS_WorkRelServiceImpl_INCLUDE
#define APS_WorkRelServiceImpl_INCLUDE
#include "../../../public/service/plan/WorkRelService.h"
#include "service/BaseService.h"

namespace aps {

class WorkRelServiceImpl : public gemini::BaseService, public WorkRelService {
  virtual void onFree(gemini::BaseEntity::SPtr entity) const;
};

}  // namespace aps
#endif  // !APS_WorkRelServiceImpl_INCLUDE