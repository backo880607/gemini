#ifndef APS_RouteStepServiceImpl_INCLUDE
#define APS_RouteStepServiceImpl_INCLUDE
#include "../../../public/service/tech/RouteStepService.h"
#include "service/BaseService.h"

namespace aps {

class RouteStepServiceImpl : public gemini::BaseService, public RouteStepService {};

}  // namespace aps
#endif  // APS_RouteStepServiceImpl_INCLUDE