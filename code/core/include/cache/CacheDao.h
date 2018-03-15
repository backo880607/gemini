#ifndef GEMINI_CacheDao_INCLUDE
#define GEMINI_CacheDao_INCLUDE
#include "../../public/Object.h"

namespace gemini {

class CacheDao : noncopyable {
protected:
	CacheDao() {}
public:
	virtual ~CacheDao() {}

	virtual std::vector<EntityObject::SPtr> select() = 0;
	virtual EntityObject::SPtr select(ID id) = 0;
	//virtual void insert(EntityObject::SPtr entity) = 0;
	//virtual void erase(ID id) = 0;
	//virtual void erase(EntityObject::SPtr entity) = 0;
	virtual void clear() = 0;

	virtual void insert(const std::map<ID, EntityObject::SPtr>& entities) = 0;
	virtual void update(const std::map<ID, EntityObject::SPtr>& entities) = 0;
	virtual void erase(const std::vector<EntityObject::SPtr>& entities) = 0;
};

}
#endif // GEMINI_CacheDao_INCLUDE