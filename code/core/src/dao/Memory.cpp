#include "dao/Memory.h"
#include "session/Subject.h"
#include "entities/FactoryMgr.h"

namespace gemini
{

Memory::Memory()
{
}

Memory::~Memory()
{
}

Memory &Memory::current()
{
	return Subject::get().getSession()->get<Memory>();
}

EntityObject::SPtr Memory::createImpl(const Class &cls, Long id)
{
	EntityObject *pEntity = (EntityObject *)cls.newInstance();
	EntityObject::SPtr entity;
	entity.wrapRawPointer(pEntity);
	FactoryMgr::instance().getFactory(cls)->createRelation(entity);
	Collector &collector = getCollector(cls);
	collector._mutex.lock();
	collector.created.insert(std::make_pair(entity->getID(), entity));
	collector._mutex.unlock();
	return entity;
}

EntityObject::SPtr Memory::create(const Class &cls, Long id)
{
	if (id > 0)
	{
		EntityObject::SPtr entity = get(cls, id);
		if (entity.valid())
		{
			return entity;
		}
	}

	return createImpl(cls, id);
}

EntityObject::SPtr Memory::createTemp(const Class &cls)
{
	EntityObject *pEntity = (EntityObject *)cls.newInstance();
	EntityObject::SPtr entity;
	entity.wrapRawPointer(pEntity);
	return entity;
}

EntityObject::SPtr Memory::get(const Class &cls, Long id)
{
	EntityObject::SPtr entity = getDao(cls)->select(id);
	if (entity.valid())
	{
		return entity;
	}

	Collector &collector = getCollector(cls);
	collector._mutex.lock();
	auto iter = collector.created.find(id);
	if (iter != collector.created.end())
	{
		entity = iter->second;
	}
	collector._mutex.unlock();
	return entity;
}

std::vector<EntityObject::SPtr> Memory::getList(const Class &cls)
{
	std::vector<EntityObject::SPtr> result;
	/*for (EntityObject::SPtr entity : getDao(cls)->select()) {
		result.push_back(entity);
	}*/

	Collector &collector = getCollector(cls);
	collector._mutex.lock();
	for (auto entry : collector.created)
	{
		result.push_back(entry.second);
	}
	collector._mutex.unlock();
	return result;
}

void Memory::sync()
{
}

} // namespace gemini