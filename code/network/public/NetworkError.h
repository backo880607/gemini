#ifndef GEMINI_NETWORK_NetworkError_INCLUDE
#define GEMINI_NETWORK_NetworkError_INCLUDE
#include "message/Exception.h"

namespace gemini {

class NetworkException : public gemini::Exception {
  virtual String getName() const override { return u8"NetworkException"; }
};

}  // namespace gemini
#endif  // GEMINI_NETWORK_NetworkError_INCLUDE
