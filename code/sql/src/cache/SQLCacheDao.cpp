#include "../../include/cache/SQLCacheDao.h"

namespace gemini
{
namespace sql
{

const IList &SQLCacheDao::select()
{
}

EntityObject::SPtr SQLCacheDao::select(ID id)
{
	return EntityObject::SPtr();
}

void SQLCacheDao::insert(EntityObject::SPtr entity)
{
}

void SQLCacheDao::erase(ID id)
{
}

void SQLCacheDao::erase(EntityObject::SPtr entity)
{
}

void SQLCacheDao::clear()
{
}

void SQLCacheDao::insert(const std::map<ID, EntityObject::SPtr> &entities)
{
}

void SQLCacheDao::update(const std::map<ID, EntityObject::SPtr> &entities)
{
}

void SQLCacheDao::erase(const std::vector<EntityObject::SPtr> &entities)
{
}

} // namespace sql
} // namespace gemini