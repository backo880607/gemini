#ifndef GEMINI_ObjectPermission_INCLUDE
#define GEMINI_ObjectPermission_INCLUDE
#include "../../../public/Common.h"

namespace gemini {

class ObjectPermission {
 public:
  virtual Boolean implies(const std::shared_ptr<ObjectPermission>& p) = 0;
};

}  // namespace gemini
#endif  // GEMINI_ObjectPermission_INCLUDE
