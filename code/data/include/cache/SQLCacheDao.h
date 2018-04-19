#ifndef GEMINI_DATA_SQLCacheDao_INCLUDE
#define GEMINI_DATA_SQLCacheDao_INCLUDE
#include "../../core/include/cache/CacheDao.h"
#include "../../public/Connection.h"

namespace gemini {
namespace data {
class SQLCacheDao : public CacheDao
{
public:
	virtual const IList& select();
	virtual EntityObject::SPtr select(ID id);
	virtual void insert(EntityObject::SPtr entity);
	virtual void erase(ID id);
	virtual void erase(EntityObject::SPtr entity);
	virtual void clear();

	virtual void insert(const std::map<ID, EntityObject::SPtr>& entities);
	virtual void update(const std::map<ID, EntityObject::SPtr>& entities);
	virtual void erase(const std::vector<EntityObject::SPtr>& entities);
private:
	Connection _conn;
};

}
}
#endif // !GEMINI_DATA_SQLCacheDao_INCLUDE
