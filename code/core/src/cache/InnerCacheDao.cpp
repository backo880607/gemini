#include "cache/InnerCacheDao.h"
#include "entities/RefVector.h"

namespace gemini {

thread_local RefVector tl_ref_dynamic;
InnerCacheDao::InnerCacheDao()
{

}

InnerCacheDao::~InnerCacheDao()
{

}

const IList& InnerCacheDao::select()
{
	tl_ref_dynamic.remove();
	std::shared_lock<boost::shared_mutex> locker(_mutex);
	for (auto iter : _entities) {
		tl_ref_dynamic.add(iter.second);
	}
	return tl_ref_dynamic;
}

EntityObject::SPtr InnerCacheDao::select(ID id)
{
	std::shared_lock<boost::shared_mutex> locker(_mutex);
	entities_type::const_iterator iter = _entities.find(id);
	return iter != _entities.end() ? iter->second : nullptr;
}

void InnerCacheDao::insert(EntityObject::SPtr entity)
{
	std::shared_lock<boost::shared_mutex> locker(_mutex);
	_entities.insert(std::make_pair(entity->getID(), entity));
}

void InnerCacheDao::erase(ID id)
{
	std::shared_lock<boost::shared_mutex> locker(_mutex);
	_entities.erase(id);
}

void InnerCacheDao::erase(EntityObject::SPtr entity)
{
	std::shared_lock<boost::shared_mutex> locker(_mutex);
	_entities.erase(entity->getID());
}

void InnerCacheDao::clear()
{
	std::unique_lock<boost::shared_mutex> lock(_mutex);
	_entities.clear();
}

void InnerCacheDao::insert(const std::map<ID, EntityObject::SPtr>& entities)
{
}

void InnerCacheDao::update(const std::map<ID, EntityObject::SPtr>& entities)
{
}

void InnerCacheDao::erase(const std::vector<EntityObject::SPtr>& entities)
{
}

}