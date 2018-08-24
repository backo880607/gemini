#include "../../../bean/tech/RouteStepIn.h"
#include "../../../include/service/tech/RouteStepInServiceImpl.h"

namespace aps {
gemini::ServiceRegister<RouteStepInServiceImpl, RouteStepInService>
    routeStepIn_service_register;
}  // namespace aps