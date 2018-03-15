#include "../../include/cache/Cache.h"
#include "../../public/session/Subject.h"
#include "../../include/entities/FactoryMgr.h"

namespace gemini {
	
Cache::Cache()
{

}

Cache::~Cache()
{

}

Cache& Cache::current()
{
	return Subject::get().getSession()->get<Cache>();
}

EntityObject::SPtr Cache::createImpl(const Class& cls, Long id)
{
	EntityObject* pEntity = (EntityObject*)cls.newInstance();
	EntityObject::SPtr entity;
	entity.wrapRawPointer(pEntity);
	FactoryMgr::instance().getFactory(cls)->createRelation(entity);
	Collector& collector = getCollector(cls);
	collector._mutex.lock();
	collector.created.insert(std::make_pair(entity->getID(), entity));
	collector._mutex.unlock();
	return entity;
}

EntityObject::SPtr Cache::create(const Class& cls, Long id)
{
	if (id > 0) {
		EntityObject::SPtr entity = get(cls, id);
		if (entity.valid()) {
			return entity;
		}
	}

	return createImpl(cls, id);
}

EntityObject::SPtr Cache::get(const Class& cls, Long id)
{
	EntityObject::SPtr entity = getDao(cls)->select(id);
	if (entity.valid()) {
		return entity;
	}

	Collector& collector = getCollector(cls);
	collector._mutex.lock();
	auto iter = collector.created.find(id);
	if (iter != collector.created.end()) {
		entity = iter->second;
	}
	collector._mutex.unlock();
	return entity;
}

std::vector<EntityObject::SPtr> Cache::getList(const Class& cls)
{
	std::vector<EntityObject::SPtr> result;
	for (EntityObject::SPtr entity : getDao(cls)->select()) {
		result.push_back(entity);
	}

	Collector& collector = getCollector(cls);
	collector._mutex.lock();
	for (auto entry : collector.created) {
		result.push_back(entry.second);
	}
	collector._mutex.unlock();
	return result;
}

void Cache::sync()
{

}

}