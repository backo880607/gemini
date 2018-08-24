#include "../../../include/service/order/MinInventoryServiceImpl.h"

namespace aps {
gemini::ServiceRegister<MinInventoryServiceImpl, MinInventoryService>
    minInventory_service_register;
}  // namespace aps