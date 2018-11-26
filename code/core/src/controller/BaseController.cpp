#include "controller/BaseController.h"
#include "controller/ControllerMgr.h"
#include "dao/DaoUtil.h"
#include "entities/IocRelation.h"
#include "expression/function/FunctionMgr.h"

namespace gemini {

void *createDto() { return nullptr; }
const Class DtoBase::_class("DtoBase", nullptr, createDto, nullptr);

DECLARE_CLASS_IMPL(BaseController, Object)

namespace exp {
RegisterFunction::RegisterFunction(const Class &cls, const String &methodName) {
  FunctionMgr::instance().registerFunction(cls, methodName);
}

RegisterFunction::~RegisterFunction() {}

RegisterReturn::RegisterReturn(const String &methodName, Int index) {
  FunctionMgr::instance().registerReturn(methodName, index);
}

RegisterReturn::~RegisterReturn() {}

RegisterArgs::RegisterArgs(const String &methodName, const String &args) {
  FunctionMgr::instance().registerArgument(methodName, args);
}

RegisterArgs::~RegisterArgs() {}
}  // namespace exp

}  // namespace gemini
