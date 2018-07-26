#ifndef APS_CommandServiceImpl_INCLUDE
#define APS_CommandServiceImpl_INCLUDE
#include "../../../public/service/instruction/CommandService.h"
#include "service/BaseService.h"

namespace aps {

class CommandServiceImpl : public gemini::BaseService, CommandService {
  SERVICE_METHOD(Command, execute)
};

}  // namespace aps
#endif  // !APS_CommandServiceImpl_INCLUDE