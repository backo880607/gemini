#ifndef GEMINI_FunctionMgr_INCLUDE
#define GEMINI_FunctionMgr_INCLUDE
#include "../../../public/ReflectMethod.h"

namespace gemini {

class FunctionMgr {
  struct Data {
    const Class *cls;
    const Method *method;
    std::map<Int, std::set<const Class *>> paramClses;
    Int returnIndex;
    Data() : cls(nullptr), method(nullptr), returnIndex(-1) {}
  };

 public:
  static FunctionMgr &instance() {
    static FunctionMgr mgr;
    return mgr;
  }

  void init();

  void registerFunction(const Class &cls, const String &name);
  void registerReturn(const String &name, Int returnIndex);
  void registerArgument(const String &name, const String &args);

  const Method *getMethod(const String &name);
  Int getReturnIndex(const String &name);
  Any invoke(const Method *method, const std::vector<Any> &params);

  void check(const Method *method,
             const std::vector<const Class *> &paramClses);

 private:
  std::map<String, Data> _functions;
};

}  // namespace gemini
#endif  // !GEMINI_FunctionMgr_INCLUDE