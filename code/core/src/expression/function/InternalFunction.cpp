#include "DateTime.h"
#include "expression/function/InternalFunction.h"
#include "tools/StringUtil.h"

namespace gemini {

Any InternalFunction::funAdd(const std::vector<Any>& params) {
  return params[0] + params[1];
}

Any InternalFunction::funSub(const std::vector<Any>& params) {
  return params[0] - params[1];
}

Any InternalFunction::funMultiply(const std::vector<Any>& params) {
  return params[0] * params[1];
}

Any InternalFunction::funDivision(const std::vector<Any>& params) {
  return params[0] / params[1];
}

Any InternalFunction::funGreater(const std::vector<Any>& params) {
  return params[0] > params[1];
}

Any InternalFunction::funGreaterEqual(const std::vector<Any>& params) {
  return params[0] >= params[1];
}

Any InternalFunction::funLess(const std::vector<Any>& params) {
  return params[0] < params[1];
}

Any InternalFunction::funLessEqual(const std::vector<Any>& params) {
  return params[0] <= params[1];
}

Any InternalFunction::funEqual(const std::vector<Any>& params) {
  return params[0] == params[1];
}

Any InternalFunction::funNotEqual(const std::vector<Any>& params) {
  return params[0] != params[1];
}

Any InternalFunction::funAnd(const std::vector<Any>& params) {
  return params[0].cast<Boolean>() && params[1].cast<Boolean>();
}

Any InternalFunction::funOr(const std::vector<Any>& params) {
  return params[0].cast<Boolean>() || params[1].cast<Boolean>();
}

Any InternalFunction::funNot(const std::vector<Any>& params) {
  return !params[0].cast<Boolean>();
}

Any InternalFunction::funToStr(const std::vector<Any>& params) {
  if (params.size() == 1) {
    return StringUtil::format(params[0]);
  }

  if (params.size() == 2) {
  }

  return nullptr;
}

Any InternalFunction::funToInt(const std::vector<Any>& params) {}

Any InternalFunction::funToDouble(const std::vector<Any>& params) {}

Any InternalFunction::funInclude(const std::vector<Any>& params) {}

Any InternalFunction::funIsInt(const std::vector<Any>& params) {
  return params[0].isType<Int>();
}

Any InternalFunction::funIsDouble(const std::vector<Any>& params) {
  return params[0].isType<Double>();
}

Any InternalFunction::funIsDigit(const std::vector<Any>& params) {
  return params[0].isType<Int>() || params[0].isType<Double>();
}

Any InternalFunction::funIsDateTime(const std::vector<Any>& params) {
  return params[0].isType<DateTime>();
}

Any InternalFunction::funIsBool(const std::vector<Any>& params) {
  return params[0].isType<Boolean>();
}

Any InternalFunction::funIsStr(const std::vector<Any>& params) {
  return params[0].isType<String>();
}

Any InternalFunction::funIsEmpty(const std::vector<Any>& params) {
  if (params.size() != 1) {
    return nullptr;
  }

  if (!params[0]) {
    return true;
  }

  if (params[0].isType<String>()) {
    return params[0].cast<String>().empty();
  }

  if (params[0].isType<DateTime>()) {
    return !params[0].cast<DateTime>().valid();
  }

  return false;
}

Any InternalFunction::funMax(const std::vector<Any>& params) {}

Any InternalFunction::funMin(const std::vector<Any>& params) {}

Any InternalFunction::funCount(const std::vector<Any>& params) {}

Any InternalFunction::funAverage(const std::vector<Any>& params) {}

Any InternalFunction::funSum(const std::vector<Any>& params) {}

Any InternalFunction::funGuard(const std::vector<Any>& params) {
  return !params[0] ? params[1] : params[0];
}

}  // namespace gemini