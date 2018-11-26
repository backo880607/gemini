#include "expression/function/FunctionMgr.h"
#include "expression/function/InternalFunction.h"
#include "message/Exception.h"
#include "tools/ClassUtil.h"
#include "tools/StringUtil.h"

namespace gemini {

void FunctionMgr::init() {
  for (std::map<String, Data>::iterator iter = _functions.begin();
       iter != _functions.end(); ++iter) {
    const Method &method = ClassUtil::getMethod(*iter->second.cls, iter->first);
    iter->second.method = &method;
  }
}

void FunctionMgr::registerFunction(const Class &cls, const String &name) {
  auto iter = _functions.find(name);
  THROW_IF(iter != _functions.end() && iter->second.method != nullptr,
           RegisterException, name, " has registed")
  _functions[name].cls = &cls;
}

void FunctionMgr::registerReturn(const String &name, Int returnIndex) {
  THROW_IF(returnIndex <= 0, MatchException, name,
           "`s returnIndex should greater than 0: ", returnIndex)
  auto iter = _functions.find(name);
  THROW_IF(iter != _functions.end() && iter->second.returnIndex > 0,
           RegisterException, name, "`s returnType has registed")
  _functions[name].returnIndex = returnIndex;
}

void FunctionMgr::registerArgument(const String &name, const String &args) {
  auto iter = _functions.find(name);
  THROW_IF(iter != _functions.end() && !iter->second.paramClses.empty(),
           RegisterException, name, "`s argument has registed")

  Data &data = _functions[name];
  StringUtil::parse<String>(args, ",", [&](String &arg) {
    Int index =
        StringUtil::convert<Int>(StringUtil::fetch_first(arg, ":").c_str());
    THROW_IF(index < 0, MatchException, name, " invalid argument index")
    StringUtil::parse<String>(arg, "|", [&](const String &type) {
      const Class &argCls = Class::forName(type);
      data.paramClses[index].insert(&argCls);
    });
  });
}

const Method *FunctionMgr::getMethod(const String &name) {
  auto iter = _functions.find(name);
  THROW_IF(iter == _functions.end(), RegisterException, name,
           " has not registed")
  return iter->second.method;
}

Int FunctionMgr::getReturnIndex(const String &name) {
  auto iter = _functions.find(name);
  THROW_IF(iter == _functions.end(), RegisterException, name,
           " has not registed")
  return iter->second.returnIndex;
}

Any FunctionMgr::invoke(const Method *method, const std::vector<Any> &params) {
  return method->invoke(this, params);
}

void FunctionMgr::check(const Method *method,
                        const std::vector<const Class *> &paramClses) {
  const std::vector<const Class *> &argsCls = method->getArgsClass();
  THROW_IF(argsCls.size() != paramClses.size(), MatchException,
           method->getName(), " not match the size of params")
  auto iter = _functions.find(method->getName());
  THROW_IF(iter == _functions.end(), RegisterException, method->getName(),
           " has not registed")
  for (auto i = 0; i < paramClses.size(); ++i) {
    auto argIter = iter->second.paramClses.find(i);
    if (argIter != iter->second.paramClses.end()) {
      THROW_IF(argIter->second.find(paramClses[i]) == argIter->second.end(),
               MatchException, method->getName(), "`s ", i,
               " params is not support ", paramClses[i]->getName())
    } else {
      THROW_IF(paramClses[i] != argsCls[i], MatchException, method->getName(),
               "`s ", i, " params is require ", argsCls[i]->getName())
    }
  }
}

}  // namespace gemini