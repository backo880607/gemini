#ifndef GEMINI_Controller_INCLUDE
#define GEMINI_Controller_INCLUDE
#include "BaseController.h"

namespace gemini {

class CORE_API ControllerMgr : noncopyable {
 public:
  static ControllerMgr& instance() {
    static ControllerMgr mgr;
    return mgr;
  }

  void init();

  const BaseController& getController(const String& name);

 private:
  std::map<String, const BaseController*> _controllers;
};

}  // namespace gemini
#endif  // !GEMINI_Controller_INCLUDE