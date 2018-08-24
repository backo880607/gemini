#ifndef GEMINI_Module_INCLUDE
#define GEMINI_Module_INCLUDE
#include "Common.h"

namespace gemini {

class CORE_API Module {
 public:
  Module();
  virtual ~Module();

  virtual void init();
  virtual void uninit();
};

CORE_API void afx_gemini_register_module(const Char* name, Module* module);
template <class T>
class ModuleRegister {
 public:
  ModuleRegister(const Char* moduleName) {
    afx_gemini_register_module(moduleName, &_module);
  }

  ~ModuleRegister() {}

  T& get() { return _module; }

 private:
  T _module;
};

#define REGISTER_MODULE(MODULE_NAME, CLASS_NAME)                          \
  gemini::ModuleRegister<CLASS_NAME> g_gemini_##CLASS_NAME(#MODULE_NAME); \
  CLASS_NAME##& afx_get##CLASS_NAME() {                             \
    return g_gemini_##CLASS_NAME.get();                                   \
  }

}  // namespace gemini
#endif  // GEMINI_Module_INCLUDE