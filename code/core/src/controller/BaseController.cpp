#include "../../public/controller/BaseController.h"
#include "../../public/controller/ControllerMgr.h"

namespace gemini {

void* createDto() { return nullptr; }
const Class DtoBase::_class("DtoBase", nullptr, createDto);

UInt BaseController::s_index = 0;
void* createBaseController() { return nullptr; }
const Class BaseController::_class("BaseController", nullptr, createBaseController);
BaseController::BaseController()
{

}

BaseController::~BaseController()
{

}

}
