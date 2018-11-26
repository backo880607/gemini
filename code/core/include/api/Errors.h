#ifndef GEMINI_API_Errors_INCLUDE
#define GEMINI_API_Errors_INCLUDE
#include "../../public/message/Message.h"

namespace gemini {
namespace api {

class ProcessLaunchError : public log_info {
 public:
  virtual String getName() override { return "ProcessLaunch"; }
};

class ProcessKillError : public log_info {
 public:
  virtual String getName() override { return "ProcessKill"; }
};

class ProcessWaitError : public log_info {
 public:
  virtual String getName() override { return "ProcessWait"; }
};

}  // namespace api
}  // namespace gemini
#endif  // GEMINI_API_Errors_INCLUDE
