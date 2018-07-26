#ifndef GEMINI_CacheUtil_INCLUDE
#define GEMINI_CacheUtil_INCLUDE
#include "../Common.h"

namespace gemini {

class CORE_API CacheUtil {
 public:
  template <typename T>
  static T &get() {}
};

}  // namespace gemini
#endif  // !GEMINI_CacheUtil_INCLUDE