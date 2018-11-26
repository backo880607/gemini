#include "entities/RefSet.h"

namespace gemini {

BaseEntity::SPtr RefSet::get() const {
  return base_type::empty() ? nullptr : *base_type::begin();
}

void RefSet::add(BaseEntity::SPtr entity) { base_type::insert(entity); }

void RefSet::remove(BaseEntity::SPtr entity) { base_type::erase(entity); }

void RefSet::remove() { base_type::clear(); }

class RefSetIterator : public IList::Iterator {
  typedef std::set<BaseEntity::WPtr> value_type;

 public:
  RefSetIterator(const value_type::const_iterator& iter,
                  const value_type& value)
      : _iter(iter), _value(value) {}

  virtual Boolean hasNext() { return _iter != _value.end(); }

 protected:
  virtual BaseEntity::SPtr nextImpl() override {
    BaseEntity::SPtr temp = *_iter;
    _iter++;
    return temp;
  }

 private:
  value_type::const_iterator _iter;
  const value_type& _value;
};

IList::Iterator RefSet::iterator() const {
  return IList::Iterator(new RefSetIterator(begin(), *this));
}

}  // namespace gemini