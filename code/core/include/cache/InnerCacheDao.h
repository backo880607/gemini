#ifndef GEMINI_InnerCacheMgr_INCLUDE
#define GEMINI_InnerCacheMgr_INCLUDE
#include "CacheDao.h"

#include <shared_mutex>

namespace gemini {

class InnerCacheDao : public CacheDao {
	typedef std::map<ID, EntityObject::SPtr> entities_type;

public:
	InnerCacheDao();
	virtual ~InnerCacheDao();

	virtual const IList& select() override;
	virtual EntityObject::SPtr select(ID id) override;
	virtual void insert(EntityObject::SPtr entity);
	virtual void erase(ID id);
	virtual void erase(EntityObject::SPtr entity);
	virtual void clear();

	virtual void insert(const std::map<ID, EntityObject::SPtr>& entities) override;
	virtual void update(const std::map<ID, EntityObject::SPtr>& entities) override;
	virtual void erase(const std::vector<EntityObject::SPtr>& entities) override;

private:
	entities_type _entities;
	std::shared_mutex _mutex;
};

}
#endif // GEMINI_InnerCacheMgr_INCLUDE