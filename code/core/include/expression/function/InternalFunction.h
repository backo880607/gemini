#ifndef GEMINI_InternalFunction_INCLUDE
#define GEMINI_InternalFunction_INCLUDE
#include "../../../public/Any.h"

namespace gemini {

class InternalFunction {
 public:
  static Any funAdd(const std::vector<Any> &params);
  static Any funSub(const std::vector<Any> &params);
  static Any funMultiply(const std::vector<Any> &params);
  static Any funDivision(const std::vector<Any> &params);
  static Any funGreater(const std::vector<Any> &params);
  static Any funGreaterEqual(const std::vector<Any> &params);
  static Any funLess(const std::vector<Any> &params);
  static Any funLessEqual(const std::vector<Any> &params);
  static Any funEqual(const std::vector<Any> &params);
  static Any funNotEqual(const std::vector<Any> &params);
  static Any funAnd(const std::vector<Any> &params);
  static Any funOr(const std::vector<Any> &params);
  static Any funNot(const std::vector<Any> &params);
  static Any funToStr(const std::vector<Any> &params);
  static Any funToInt(const std::vector<Any> &params);
  static Any funToDouble(const std::vector<Any> &params);
  static Any funInclude(const std::vector<Any> &params);
  static Any funIsInt(const std::vector<Any> &params);
  static Any funIsDouble(const std::vector<Any> &params);
  static Any funIsDigit(const std::vector<Any> &params);
  static Any funIsDateTime(const std::vector<Any> &params);
  static Any funIsBool(const std::vector<Any> &params);
  static Any funIsStr(const std::vector<Any> &params);
  static Any funIsEmpty(const std::vector<Any> &params);
  static Any funMax(const std::vector<Any> &params);
  static Any funMin(const std::vector<Any> &params);
  static Any funCount(const std::vector<Any> &params);
  static Any funAverage(const std::vector<Any> &params);
  static Any funSum(const std::vector<Any> &params);
  static Any funGuard(const std::vector<Any> &params);
};

}  // namespace gemini
#endif  // !GEMINI_InternalFunction_INCLUDE