#ifndef GEMINI_EntityFunction_INCLUDE
#define GEMINI_EntityFunction_INCLUDE
#include "../../../public/Any.h"

namespace gemini {

class EntityFunction {
 public:
  static Any funIsType(const std::vector<Any> &params);
  static Any funAsType(const std::vector<Any> &params);
};

}  // namespace gemini
#endif  // !GEMINI_EntityFunction_INCLUDE