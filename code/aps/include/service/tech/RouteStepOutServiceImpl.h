#ifndef APS_RouteStepOutServiceImpl_INCLUDE
#define APS_RouteStepOutServiceImpl_INCLUDE
#include "../../../public/service/tech/RouteStepOutService.h"
#include "service/BaseService.h"

namespace aps {

class RouteStepOutServiceImpl : public gemini::BaseService,
                                public RouteStepOutService {};

}  // namespace aps
#endif  // APS_RouteStepOutServiceImpl_INCLUDE