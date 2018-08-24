#include "../../../bean/mstr/Resource.h"
#include "../../../include/service/mstr/ResourceServiceImpl.h"

namespace aps {
gemini::ServiceRegister<ResourceServiceImpl, ResourceService>
    resource_service_register;
}  // namespace aps