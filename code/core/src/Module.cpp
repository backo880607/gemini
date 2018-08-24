#include "Module.h"
#include "Application.h"

namespace gemini {

Module::Module() {}

Module::~Module() {}

void Module::init() {}

void Module::uninit() {}

void afx_gemini_register_module(const Char* name, Module* module) {
  g_app.registerModule(name, module);
}

}  // namespace gemini