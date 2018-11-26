#ifndef GEMINI_RefEntity_INCLUDE
#define GEMINI_RefEntity_INCLUDE
#include "RefBase.h"

namespace gemini {

class RefEntity : public RefBase {
 public:
  virtual BaseEntity::SPtr get() const { return _entity; }
  virtual void add(BaseEntity::SPtr entity);
  virtual void remove(BaseEntity::SPtr entity);
  virtual void remove();

  virtual Boolean empty() const { return !_entity.valid(); }
  virtual Long size() const { return empty() ? 0 : 1; }
  virtual Iterator iterator() const;

 private:
  BaseEntity::WPtr _entity;
};

}  // namespace gemini
#endif  // GEMINI_RefEntity_INCLUDE