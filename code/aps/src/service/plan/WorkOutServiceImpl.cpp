#include "../../../include/service/plan/WorkOutServiceImpl.h"
#include "../../../bean/plan/WorkOut.h"

namespace aps {
gemini::ServiceRegister<WorkOutServiceImpl, WorkOutService>
    workOut_service_register;
}