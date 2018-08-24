#include "../../../bean/tech/Route.h"
#include "../../../include/service/tech/RouteServiceImpl.h"

namespace aps {
gemini::ServiceRegister<RouteServiceImpl, RouteService> route_service_register;
}  // namespace aps