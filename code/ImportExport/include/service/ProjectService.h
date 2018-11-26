#ifndef GEMINI_INTEGRATION_ProjectService_INCLUDE
#define GEMINI_INTEGRATION_ProjectService_INCLUDE
#include "../../public/service/IProjectService.h"
#include "service/BaseService.h"

namespace gemini {
namespace integration {

class ProjectService : public BaseService, public IProjectService {};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_ProjectService_INCLUDE