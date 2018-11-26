#include "entities/RefEntity.h"

namespace gemini {

void RefEntity::add(BaseEntity::SPtr entity) { _entity = entity; }

void RefEntity::remove(BaseEntity::SPtr entity) {
  if (_entity == entity) {
    _entity = nullptr;
  }
}

void RefEntity::remove() { _entity = nullptr; }

class EntityIterator : public IList::Iterator {
 public:
  EntityIterator(const BaseEntity::SPtr& entity)
      : _begin(true), _entity(entity) {}
  virtual Boolean hasNext() { return _begin == true; }

 protected:
  virtual BaseEntity::SPtr nextImpl() override {
    _begin = false;
    return _entity;
  }

 private:
  Boolean _begin;
  const BaseEntity::SPtr& _entity;
};

IList::Iterator RefEntity::iterator() const {
  return IList::Iterator(new EntityIterator(_entity));
}

}  // namespace gemini