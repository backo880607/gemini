#ifndef GEMINI_RefVector_INCLUDE
#define GEMINI_RefVector_INCLUDE
#include "RefBase.h"

namespace gemini {

class RefVector : public RefBase, std::vector<EntityObject::SPtr>
{
	typedef std::vector<EntityObject::SPtr> base_type;
public:
	virtual EntityObject::SPtr get();
	virtual void add(EntityObject::SPtr entity);
	virtual void remove(EntityObject::SPtr entity);
	virtual void remove();

	virtual Boolean empty() { return base_type::empty(); }
	virtual Long size() { return base_type::size(); }
	virtual Iterator iterator() const;
};

}
#endif // GEMINI_RefVector_INCLUDE