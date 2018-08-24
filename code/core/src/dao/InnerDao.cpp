#include "dao/InnerDao.h"
#include "entities/RefVector.h"

namespace gemini {

thread_local RefVector tl_ref_dynamic;
DECLARE_CLASS_IMPL(InnerDao, BaseDao)
const IList &InnerDao::select() {
  tl_ref_dynamic.remove();
  std::unique_lock<std::mutex> locker(_mutex);
  for (auto iter : _entities) {
    tl_ref_dynamic.add(iter.second);
  }
  return tl_ref_dynamic;
}

EntityObject::SPtr InnerDao::select(ID id) {
  std::unique_lock<std::mutex> locker(_mutex);
  entities_type::const_iterator iter = _entities.find(id);
  return iter != _entities.end() ? iter->second : nullptr;
}

void InnerDao::insert(EntityObject::SPtr entity) {
  std::unique_lock<std::mutex> locker(_mutex);
  _entities.insert(std::make_pair(entity->getID(), entity));
}

void InnerDao::update(EntityObject::SPtr entity) {}

void InnerDao::erase(ID id) {
  std::unique_lock<std::mutex> locker(_mutex);
  _entities.erase(id);
}

void InnerDao::erase(EntityObject::SPtr entity) {
  return erase(entity->getID());
}

void InnerDao::clear() {
  std::unique_lock<std::mutex> lock(_mutex);
  _entities.clear();
}

void InnerDao::insert(const std::vector<EntityObject::SPtr> &entities) {
  std::unique_lock<std::mutex> locker(_mutex);
  for (EntityObject::SPtr entity : entities) {
    _entities.insert(std::make_pair(entity->getID(), entity));
  }
}

void InnerDao::update(const std::vector<EntityObject::SPtr> &entities) {}

void InnerDao::erase(const std::vector<EntityObject::SPtr> &entities) {
  std::unique_lock<std::mutex> locker(_mutex);
  for (EntityObject::SPtr entity : entities) {
    _entities.erase(entity->getID());
  }
}

}  // namespace gemini