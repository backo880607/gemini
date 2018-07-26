#ifndef GEMINI_ExpressionUtil_INCLUDE
#define GEMINI_ExpressionUtil_INCLUDE
#include "../Any.h"

namespace gemini {

class ExpressionUtil {
  typedef Any (*Fun)(const std::vector<Any>&);

 private:
 public:
  ExpressionUtil();
  ~ExpressionUtil();

  static void registerFunction(const String& name, Fun fun);

  template <typename R, class C>
  static Any call(const std::vector<Any>& params) {}
  template <typename R, class C, typename P1>
  static Any call(const std::vector<Any>& params) {}
};

}  // namespace gemini
#endif  // !GEMINI_ExpressionUtil_INCLUDE