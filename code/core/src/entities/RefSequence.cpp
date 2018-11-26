#include "entities/RefSequence.h"

namespace gemini {

BaseEntity::SPtr RefSequence::get() const {
  return base_type::empty() ? nullptr : base_type::front();
}

void RefSequence::add(BaseEntity::SPtr entity) {
  base_type::push_back(entity);
}

void RefSequence::remove(BaseEntity::SPtr entity) {
  base_type::remove(entity);
}

void RefSequence::remove() { base_type::clear(); }

class RefSequenceIterator : public IList::Iterator {
  typedef std::list<BaseEntity::WPtr> value_type;

 public:
  RefSequenceIterator(const value_type::const_iterator& iter,
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

IList::Iterator RefSequence::iterator() const {
  return IList::Iterator(new RefSequenceIterator(begin(), *this));
}

}  // namespace gemini