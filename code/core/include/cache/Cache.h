#ifndef GEMINI_Cache_INCLUDE
#define GEMINI_Cache_INCLUDE
#include "CacheMgr.h"

#include <mutex>

namespace gemini {

class Cache final : noncopyable {
private:
	struct Collector {
		std::mutex _mutex;
		std::map<ID, EntityObject::SPtr> created;
		std::map<ID, EntityObject::SPtr> modified;
		std::vector<EntityObject::SPtr> deleted;
	};

	static Cache& current();
	static Collector& getCollector(const Class& cls) { return current()._alterations[cls.index()]; }
	static std::shared_ptr<CacheDao> getDao(const Class& cls) { return current()._cacheMgr.getDao(cls); }

	friend class Session;
	Cache();
public:
	~Cache();

	static EntityObject::SPtr get(const Class& cls) {
		return current()._singletons[cls.index()];
	}

	static EntityObject::SPtr create(const Class& cls, Long id);

	static EntityObject::SPtr get(const Class& cls, Long id);

	static std::vector<EntityObject::SPtr> getList(const Class& cls);

	static void sync();

private:
	static EntityObject::SPtr createImpl(const Class& cls, Long id);

private:
	std::vector<Collector> _alterations;
	std::vector<Object::SPtr> _singletons;
	CacheMgr _cacheMgr;
};

}
#endif // GEMINI_Cache_INCLUDE