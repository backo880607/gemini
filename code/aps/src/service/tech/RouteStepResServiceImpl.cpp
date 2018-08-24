#include "../../../bean/tech/RouteStepRes.h"
#include "../../../include/service/tech/RouteStepResServiceImpl.h"

namespace aps {
gemini::ServiceRegister<RouteStepResServiceImpl, RouteStepResService>
    routeStepRes_service_register;
}  // namespace aps