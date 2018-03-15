#include "../../include/Entities/RefList.h"

namespace gemini {

EntityObject::SPtr RefList::get()
{
	return base_type::empty() ? nullptr : base_type::front();
}

void RefList::add(EntityObject::SPtr entity)
{
	base_type::push_back(entity);
}

void RefList::remove(EntityObject::SPtr entity)
{
	base_type::remove(entity);
}

void RefList::remove()
{
	base_type::clear();
}

class RefListIterator : public IList::Iterator
{
	typedef std::list<EntityObject::SPtr> value_type;
public:
	RefListIterator(const value_type::const_iterator& iter, const value_type& value) : _iter(iter), _value(value) {}

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

IList::Iterator RefList::iterator() const
{
	return IList::Iterator(new RefListIterator(begin(), *this));
}

}