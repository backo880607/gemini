#include "../../../bean/plan/WorkFdbk.h"
#include "../../../include/service/plan/WorkFdbkServiceImpl.h"

namespace aps {
gemini::ServiceRegister<WorkFdbkServiceImpl, WorkFdbkService>
    workFdbk_service_register;
}