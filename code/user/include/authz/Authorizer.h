#ifndef GEMINI_USER_Authorizer_INCLUDE
#define GEMINI_USER_Authorizer_INCLUDE
#include "Common.h"

namespace gemini {
namespace user {

class Authorizer {
 public:
  virtual ~Authorizer() {}
  virtual Boolean isPermitted(const String& principal,
                              const String& permission) = 0;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_Authorizer_INCLUDE