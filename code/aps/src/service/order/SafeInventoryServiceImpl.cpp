#include "../../../include/service/order/SafeInventoryServiceImpl.h"

namespace aps {
gemini::ServiceRegister<SafeInventoryServiceImpl, SafeInventoryService>
    safeInventory_service_register;
}  // namespace aps