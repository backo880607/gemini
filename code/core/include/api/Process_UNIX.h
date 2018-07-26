#ifndef GEMINI_Process_UNIX_include
#define GEMINI_Process_UNIX_include
#include "../../public/Common.h"

#if GEMINI_OS == GEMINI_OS_LINUX || GEMINI_OS == GEMINI_OS_MAC_OS_X
#include <unistd.h>

namespace gemini {

class ProcessImpl {
  typedef std::vector<String> Args;

 public:
  ProcessImpl(Long pid);
  ~ProcessImpl();

  Long id() const;
  Boolean running() const;
  Int wait() const;
  void killImpl();

  static Long currentId();
  static std::shared_ptr<ProcessImpl> launch(const String& command,
                                             const Args& args);

 private:
  pid_t _pid;
};

}  // namespace gemini
#endif

#endif  // GEMINI_Process_UNIX_include
