#ifndef GEMINI_USER_ObjectPermission_INCLUDE
#define GEMINI_USER_ObjectPermission_INCLUDE
#include "Common.h"

namespace gemini {
namespace user {

class ObjectPermission {
 public:
  virtual Boolean implies(const std::shared_ptr<ObjectPermission>& p) = 0;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_ObjectPermission_INCLUDE