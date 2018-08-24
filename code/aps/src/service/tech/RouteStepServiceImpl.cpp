#include "../../../bean/tech/RouteStep.h"
#include "../../../include/service/tech/RouteStepServiceImpl.h"

namespace aps {
gemini::ServiceRegister<RouteStepServiceImpl, RouteStepService>
    routeStep_service_register;
}  // namespace aps