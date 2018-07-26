#ifndef GEMINI_TextFunction_INCLUDE
#define GEMINI_TextFunction_INCLUDE
#include "../../../public/Any.h"

namespace gemini {

class TextFunction {
 public:
  static Any funClean(const std::vector<Any> &params);
};

}  // namespace gemini
#endif  // !GEMINI_TextFunction_INCLUDE