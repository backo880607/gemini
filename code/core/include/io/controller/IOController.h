#ifndef GEMINI_IOController_INCLUDE
#define GEMINI_IOController_INCLUDE
#include "../../../public/controller/BaseController.h"

namespace gemini
{

class IOController : public BaseController
{
    DECLARE_CLASS(IOController, BaseController)

  public:
    CONTROLLER_METHOD(void, execute, (String name));
};
} // namespace gemini
#endif // !GEMINI_IOController_INCLUDEBaseCon