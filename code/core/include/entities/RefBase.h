#ifndef GEMINI_RefBase_INCLUDE
#define GEMINI_RefBase_INCLUDE
#include "../../public/Object.h"

namespace gemini {

class RefBase : public IList
{
public:
	RefBase() {}
	virtual ~RefBase() {}
	virtual EntityObject::SPtr get() const = 0;
	virtual void add(EntityObject::SPtr entity) = 0;
	virtual void remove(EntityObject::SPtr entity) = 0;
	virtual void remove() = 0;
};

}
#endif // GEMINI_RefBase_INCLUDE