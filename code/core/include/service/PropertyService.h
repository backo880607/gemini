#ifndef GEMINI_PropertyService_INCLUDE
#define GEMINI_PropertyService_INCLUDE
#include "../../public/service/IPropertyService.h"
#include "../../public/service/BaseService.h"

namespace gemini {

class PropertyService : public BaseService, public IPropertyService {};

}  // namespace gemini
#endif  // GEMINI_PropertyService_INCLUDE