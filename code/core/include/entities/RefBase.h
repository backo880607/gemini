#ifndef GEMINI_RefBase_INCLUDE
#define GEMINI_RefBase_INCLUDE
#include "Object.h"

namespace gemini {

class RefBase : public IList {
 public:
  RefBase() {}
  virtual ~RefBase() {}
  virtual BaseEntity::SPtr get() const = 0;
  virtual void add(BaseEntity::SPtr entity) = 0;
  virtual void remove(BaseEntity::SPtr entity) = 0;
  virtual void remove() = 0;
};

}  // namespace gemini
#endif  // GEMINI_RefBase_INCLUDE