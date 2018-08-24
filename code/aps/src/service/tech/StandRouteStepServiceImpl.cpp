#include "../../../bean/tech/StandRouteStep.h"
#include "../../../include/service/tech/StandRouteStepServiceImpl.h"

namespace aps {
gemini::ServiceRegister<StandRouteStepServiceImpl, StandRouteStepService>
    standRouteStep_service_register;
}  // namespace aps