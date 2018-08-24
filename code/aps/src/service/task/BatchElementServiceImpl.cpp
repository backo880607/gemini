#include "../../../bean/task/BatchElement.h"
#include "../../../include/service/task/BatchElementServiceImpl.h"

namespace aps {
gemini::ServiceRegister<BatchElementServiceImpl, BatchElementService>
    batchElement_service_register;
}  // namespace aps