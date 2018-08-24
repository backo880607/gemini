#include "../../../include/service/plan/WorkResServiceImpl.h"
#include "../../../bean/plan/WorkRes.h"

namespace aps {
gemini::ServiceRegister<WorkResServiceImpl, WorkResService>
    workRes_service_register;
}