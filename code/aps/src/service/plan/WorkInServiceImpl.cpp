#include "../../../include/service/plan/WorkInServiceImpl.h"
#include "../../../bean/plan/WorkIn.h"

namespace aps {
gemini::ServiceRegister<WorkInServiceImpl, WorkInService>
    workIn_service_register;
}