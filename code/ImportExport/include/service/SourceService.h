#ifndef GEMINI_INTEGRATION_SourceService_INCLUDE
#define GEMINI_INTEGRATION_SourceService_INCLUDE
#include "../../public/service/ISourceService.h"
#include "service/BaseService.h"

namespace gemini {
namespace integration {

class SourceService : public BaseService, public ISourceService {};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_SourceService_INCLUDE