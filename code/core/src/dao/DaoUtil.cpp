#include "dao/DaoUtil.h"
#include "entities/FactoryMgr.h"
#include "Session.h"

namespace gemini {

DaoUtil::DaoUtil() {}

DaoUtil::~DaoUtil() {}

std::shared_ptr<BaseDao> DaoUtil::getDao(const Class &cls) {
  std::shared_ptr<BaseDao> dao = DaoMgr::getGlobalDao(cls);
  if (dao != nullptr) {
    return dao;
  }
  DaoMgr &daoMgr = getSession()->getDaoMgr();
  return daoMgr.getDao(cls);
}

BaseEntity::SPtr DaoUtil::createImpl(const Class &cls, ID id) {
  BaseEntity *pEntity = (BaseEntity *)cls.newInstance();
  if (id > 0) {
    pEntity->_id = id;
  }
  BaseEntity::SPtr entity;
  entity.wrapRawPointer(pEntity);
  FactoryMgr::instance().getFactory(cls)->createRelation(entity);
  getDao(cls)->insert(entity);
  return entity;
}

BaseEntity::SPtr DaoUtil::create(const Class &cls, ID id) {
  if (id > 0) {
    BaseEntity::SPtr entity = get(cls, id);
    if (entity.valid()) {
      return entity;
    }
  }

  return createImpl(cls, id);
}

BaseEntity::SPtr DaoUtil::createTemp(const Class &cls) {
  BaseEntity *pEntity = (BaseEntity *)cls.newInstance();
  BaseEntity::SPtr entity;
  entity.wrapRawPointer(pEntity);
  FactoryMgr::instance().getFactory(cls)->createRelation(entity);
  return entity;
}

BaseEntity::SPtr DaoUtil::get(const Class &cls) { return get(cls, 0); }

BaseEntity::SPtr DaoUtil::get(const Class &cls, ID id) {
  return getDao(cls)->select(id);
}

const IList &DaoUtil::getList(const Class &cls) {
  return getDao(cls)->select();
}

void DaoUtil::insert(const BaseEntity::SPtr &entity) {
  getDao(entity->getClass())->insert(entity);
}

void DaoUtil::update(const BaseEntity *entity) {}

void DaoUtil::erase(const Class &cls, ID id) { getDao(cls)->erase(id); }

void DaoUtil::erase(const BaseEntity *entity) {
  getDao(entity->getClass())->erase(entity->getID());
}

void DaoUtil::clear(const Class &cls) { getDao(cls)->clear(); }

void DaoUtil::sync() {
  DaoMgr &daoMgr = getSession()->getDaoMgr();
  daoMgr.startSync();
  std::vector<DaoMgr::dao_type> &daoes = daoMgr.getDaoes();
  for (DaoMgr::dao_type dao : daoes) {
    if (dao == nullptr) {
      continue;
    }
    dao->sync();
  }
  daoMgr.endSync();
}

}  // namespace gemini