#include "../../include/service/PropertyService.h"

namespace gemini {
gemini::ServiceRegister<PropertyService, IPropertyService>
    property_service_register;
}