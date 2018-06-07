#ifndef GEMINI_RefList_INCLUDE
#define GEMINI_RefList_INCLUDE

#include "RefBase.h"

namespace gemini {

class RefList : public RefBase, std::list<EntityObject::SPtr>
{
	typedef std::list<EntityObject::SPtr> base_type;
public:
	virtual EntityObject::SPtr get() const;
	virtual void add(EntityObject::SPtr entity);
	virtual void remove(EntityObject::SPtr entity);
	virtual void remove();

	virtual Boolean empty() const { return base_type::empty(); }
	virtual Long size() const { return base_type::size(); }
	virtual Iterator iterator() const;
};

}
#endif // GEMINI_RefList_INCLUDE