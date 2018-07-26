#ifndef GEMINI_PROPAGATE_Errors_INCLUDE
#define GEMINI_PROPAGATE_Errors_INCLUDE
#include "../../public/message/Message.h"

namespace gemini {

class CycleError : public log_info {
 public:
  virtual String getName() override { return u8"Cycle"; }
};

}  // namespace gemini
#endif  // GEMINI_PROPAGATE_Errors_INCLUDE