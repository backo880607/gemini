#ifndef APS_RouteStepInServiceImpl_INCLUDE
#define APS_RouteStepInServiceImpl_INCLUDE
#include "../../../public/service/tech/RouteStepInService.h"
#include "service/BaseService.h"

namespace aps {

class RouteStepInServiceImpl : public gemini::BaseService,
                               RouteStepInService {};

}  // namespace aps
#endif  // APS_RouteStepInServiceImpl_INCLUDE