#include "expression/function/EntityFunction.h"

namespace gemini {

Any EntityFunction::funIsType(const std::vector<Any>& params) {
  return params[0].getClass().getName() == params[1].cast<String>();
}

Any EntityFunction::funAsType(const std::vector<Any>& params) { return Any(); }

}  // namespace gemini