#ifndef GEMINI_FunctionMgr_INCLUDE
#define GEMINI_FunctionMgr_INCLUDE
#include "../../../public/ReflectMethod.h"

namespace gemini {

class FunctionMgr {
 public:
  static FunctionMgr &instance() {
    static FunctionMgr mgr;
    return mgr;
  }

  void registerFunction(const Class &cls, const String &name);

  const Method *getMethod(const String &name);
  Any invoke(const Method *method, const std::vector<Any> &params);

 private:
  std::map<String, const Method *> _functions;
};

}  // namespace gemini
#endif  // !GEMINI_FunctionMgr_INCLUDE