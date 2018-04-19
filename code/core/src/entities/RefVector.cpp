#include "entities/RefVector.h"

namespace gemini {

EntityObject::SPtr RefVector::get()
{
	return base_type::empty() ? nullptr : base_type::operator[](0);
}

void RefVector::add(EntityObject::SPtr entity)
{
	base_type::push_back(entity);
}

void RefVector::remove(EntityObject::SPtr entity)
{
	
}

void RefVector::remove()
{
	base_type::clear();
}

class RefVectorIterator : public IList::Iterator
{
	typedef std::vector<EntityObject::SPtr> value_type;
public:
	RefVectorIterator(const value_type::const_iterator& iter, const value_type& value) : _iter(iter), _value(value) {}

	virtual Boolean hasNext() {
		return _iter != _value.end();
	}

protected:
	virtual const EntityObject::SPtr& nextImpl() {
		const EntityObject::SPtr& temp = *_iter;
		_iter++;
		return temp;
	}
private:
	value_type::const_iterator _iter;
	const value_type& _value;
};

IList::Iterator RefVector::iterator() const
{
	return IList::Iterator(new RefVectorIterator(begin(), *this));
}

}