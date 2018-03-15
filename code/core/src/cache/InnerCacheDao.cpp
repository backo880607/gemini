#include "../../include/cache/InnerCacheDao.h"

namespace gemini {

InnerCacheDao::InnerCacheDao()
{

}

InnerCacheDao::~InnerCacheDao()
{

}

std::vector<EntityObject::SPtr> InnerCacheDao::select()
{
	std::vector<EntityObject::SPtr> result;
	std::shared_lock<std::shared_mutex> locker(_mutex);
	for (auto iter : _entities) {
		result.push_back(iter.second);
	}
	return result;
}

EntityObject::SPtr InnerCacheDao::select(ID id)
{
	std::shared_lock<std::shared_mutex> locker(_mutex);
	entities_type::const_iterator iter = _entities.find(id);
	return iter != _entities.end() ? iter->second : nullptr;
}

void InnerCacheDao::clear()
{
	std::unique_lock<std::shared_mutex> lock(_mutex);
	_entities.clear();
}

void InnerCacheDao::insert(const std::map<ID, EntityObject::SPtr>& entities)
{
	std::unique_lock<std::shared_mutex> lock(_mutex);
	for (auto iter : entities) {
		_entities[iter.first] = iter.second;
	}
}

void InnerCacheDao::update(const std::map<ID, EntityObject::SPtr>& entities)
{

}

void InnerCacheDao::erase(const std::vector<EntityObject::SPtr>& entities)
{
	std::unique_lock<std::shared_mutex> lock(_mutex);
	for (EntityObject::SPtr entity : entities) {
		_entities.erase(entity.getID());
	}
}

}