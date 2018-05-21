#ifndef APS_CommandService_INCLUDE
#define APS_CommandService_INCLUDE
#include "service/IBaseService.h"

namespace aps
{
class Command;
class CommandService : public gemini::IBaseService
{
  public:
    SERVICE_INTERFACE_METHOD(Command, execute)
};
} // namespace aps

#endif // !APS_CommandService_INCLUDE