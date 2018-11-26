#ifndef GEMINI_INTEGRATION_SchemeService_INCLUDE
#define GEMINI_INTEGRATION_SchemeService_INCLUDE
#include "../../public/service/ISchemeService.h"
#include "service/BaseService.h"

namespace gemini {
namespace integration {

class SchemeService : public BaseService, public ISchemeService {};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_SchemeService_INCLUDE