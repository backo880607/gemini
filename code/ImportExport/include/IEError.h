#ifndef GEMINI_INTEGRATION_IEError_INCLUDE
#define GEMINI_INTEGRATION_IEError_INCLUDE
#include "message/Exception.h"

namespace gemini {
namespace integration {

class InvalidDataSource : public log_info {
  virtual String getName() override { return "InvalidDataSource"; }
};

}  // namespace integration
}  // namespace gemini
#endif  // GEMINI_INTEGRATION_IEError_INCLUDE