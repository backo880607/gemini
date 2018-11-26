#include "entities/RefVector.h"

namespace gemini {

BaseEntity::SPtr RefVector::get() const {
  return base_type::empty() ? nullptr : base_type::operator[](0);
}

void RefVector::add(BaseEntity::SPtr entity) { base_type::push_back(entity); }

void RefVector::remove(BaseEntity::SPtr entity) {}

void RefVector::remove() { base_type::clear(); }

class RefVectorIterator : public IList::Iterator {
  typedef std::vector<BaseEntity::WPtr> value_type;

 public:
  RefVectorIterator(const value_type::const_iterator& iter,
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

IList::Iterator RefVector::iterator() const {
  return IList::Iterator(new RefVectorIterator(begin(), *this));
}

}  // namespace gemini