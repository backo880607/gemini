#include "expression/function/FunctionMgr.h"
#include "expression/function/InternalFunction.h"
#include "message/Exception.h"

namespace gemini {

void FunctionMgr::registerFunction(const Class &cls, const String &name) {
  auto iter = _functions.find(name);
  THROW_IF(iter != _functions.end(), RegisterException, name, " has registed")
  const Method &method = cls.getMethod(name);
  _functions.insert(std::make_pair(name, &method));
}

const Method *FunctionMgr::getMethod(const String &name) {
  auto iter = _functions.find(name);
  THROW_IF(iter == _functions.end(), RegisterException, name,
           " has not registed")
  return iter->second;
}

Any FunctionMgr::invoke(const Method *method, const std::vector<Any> &params) {
  const std::vector<const Class *> &argsCls = method->getArgsClass();
  THROW_IF(argsCls.size() != params.size(), MatchException, method->getName(),
           " not match the size of params")
  for (Long i = 0; i < params.size(); ++i) {
    THROW_IF(params[i].getClass() != *argsCls[i], MatchException,
             method->getName(), i, " of params is require ",
             argsCls[i]->getName())
  }

  method->invoke(this, params);
}

}  // namespace gemini