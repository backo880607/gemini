#ifndef APS_ParentWorkServiceImpl_INCLUDE
#define APS_ParentWorkServiceImpl_INCLUDE
#include "../../../public/service/plan/ParentWorkService.h"
#include "service/BaseService.h"

namespace aps {
class ParentWorkServiceImpl : public gemini::BaseService, ParentWorkService {};
}  // namespace aps
#endif  // !APS_ParentWorkServiceImpl_INCLUDE