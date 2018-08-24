#include "../../../bean/tech/RouteStepOut.h"
#include "../../../include/service/tech/RouteStepOutServiceImpl.h"

namespace aps {
gemini::ServiceRegister<RouteStepOutServiceImpl, RouteStepOutService>
    routeStepOut_service_register;
}  // namespace aps