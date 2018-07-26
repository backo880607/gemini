#include "expression/function/LogicFunction.h"

namespace gemini {

Any LogicFunction::funTrue(const std::vector<Any>& params) { return true; }

Any LogicFunction::funFalse(const std::vector<Any>& params) { return false; }

Any LogicFunction::funIf(const std::vector<Any>& params) {
  return params[0].cast<Boolean>() ? params[1] : params[2];
}

Any LogicFunction::funNot(const std::vector<Any>& params) {
  return !params[0].cast<Boolean>();
}

Any LogicFunction::funOr(const std::vector<Any>& params) {
  for (const Any& param : params) {
    if (param.cast<Boolean>()) {
      return true;
    }
  }
  return false;
}

Any LogicFunction::funXor(const std::vector<Any>& params) {}

}  // namespace gemini