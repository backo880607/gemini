#include "dao/Memory.h"
#include "entities/FactoryMgr.h"
#include "session/Subject.h"

namespace gemini {

Memory::Memory() {}

Memory::~Memory() {}

Memory &Memory::current() { return Subject::get().getSession()->get<Memory>(); }

EntityObject::SPtr Memory::createImpl(const Class &cls, Long id) {
  EntityObject *pEntity = (EntityObject *)cls.newInstance();
  EntityObject::SPtr entity;
  entity.wrapRawPointer(pEntity);
  FactoryMgr::instance().getFactory(cls)->createRelation(entity);
  return entity;
}

EntityObject::SPtr Memory::create(const Class &cls, Long id) {
  if (id > 0) {
    EntityObject::SPtr entity = get(cls, id);
    if (entity.valid()) {
      return entity;
    }
  }

  return createImpl(cls, id);
}

EntityObject::SPtr Memory::createTemp(const Class &cls) {
  EntityObject *pEntity = (EntityObject *)cls.newInstance();
  EntityObject::SPtr entity;
  entity.wrapRawPointer(pEntity);
  return entity;
}

EntityObject::SPtr Memory::get(const Class &cls) { return get(cls, 0); }

EntityObject::SPtr Memory::get(const Class &cls, Long id) {
  return getDao(cls)->select(id);
}

const IList &Memory::getList(const Class &cls) { return getDao(cls)->select(); }

void Memory::update(const EntityObject *entity) {}

void Memory::erase(const Class &cls, ID id) { getDao(cls)->erase(id); }

void Memory::erase(const EntityObject *entity) {
  getDao(entity->getClass())->erase(entity->getID());
}

void Memory::clear(const Class &cls) { getDao(cls)->clear(); }

void Memory::sync() {
  std::vector<DaoMgr::dao_type> &daoes = current()._daoMgr.getDaoes();
  for (DaoMgr::dao_type dao : daoes) {
    dao->sync();
  }
}

}  // namespace gemini