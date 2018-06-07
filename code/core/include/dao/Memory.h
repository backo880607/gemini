#ifndef GEMINI_Memory_INCLUDE
#define GEMINI_MemoryINCLUDE
#include "DaoMgr.h"

#include <mutex>

namespace gemini
{

class Memory final : noncopyable
{
  private:
	struct Collector
	{
		std::mutex _mutex;
		std::map<ID, EntityObject::SPtr> created;
		std::map<ID, EntityObject::SPtr> modified;
		std::vector<EntityObject::SPtr> deleted;
	};

	static Memory &current();
	static Collector &getCollector(const Class &cls) { return current()._alterations[cls.index()]; }
	static std::shared_ptr<BaseDao> getDao(const Class &cls) { return current()._daoMgr.getDao(cls); }

	friend class Session;
	Memory();

  public:
	~Memory();

	static EntityObject::SPtr get(const Class &cls)
	{
		return current()._singletons[cls.index()];
	}

	static EntityObject::SPtr create(const Class &cls, Long id);
	static EntityObject::SPtr createTemp(const Class &cls);

	static EntityObject::SPtr get(const Class &cls, Long id);

	static std::vector<EntityObject::SPtr> getList(const Class &cls);

	static void sync();

  private:
	static EntityObject::SPtr createImpl(const Class &cls, Long id);

  private:
	std::vector<Collector> _alterations;
	std::vector<Object::SPtr> _singletons;
	DaoMgr _daoMgr;
};

} // namespace gemini
#endif // GEMINI_Memory_INCLUDE