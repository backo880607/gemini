#ifndef GEMINI_RefEntity_INCLUDE
#define GEMINI_RefEntity_INCLUDE

#include "RefBase.h"

namespace gemini {

class RefEntity : public RefBase {
 public:
  virtual EntityObject::SPtr get() const { return _entity; }
  virtual void add(EntityObject::SPtr entity);
  virtual void remove(EntityObject::SPtr entity);
  virtual void remove();

  virtual Boolean empty() const { return !_entity.valid(); }
  virtual Long size() const { return empty() ? 0 : 1; }
  virtual Iterator iterator() const;

 private:
  EntityObject::SPtr _entity;
};

}  // namespace gemini
#endif  // GEMINI_RefEntity_INCLUDE