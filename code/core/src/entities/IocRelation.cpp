#include "entities/EntityFactory.h"
#include "entities/FactoryMgr.h"
#include "entities/IocRelation.h"
#include "entities/RefVector.h"

namespace gemini {

thread_local RefVector tl_ref_dynamic2;
BaseEntity::SPtr IocRelation::getImpl(BaseEntity::SPtr entity,
                                        std::vector<Int>::const_iterator iter,
                                        const std::vector<Int>& signs) {
  if (iter == signs.end()) {
    return entity;
  } else {
    IList::Iterator relaIter = entity->_relations[*iter++]->iterator();
    while (relaIter.hasNext()) {
      BaseEntity::SPtr result =
          getImpl(relaIter.next<BaseEntity>(), iter, signs);
      if (result.valid()) {
        return result;
      }
    }
  }

  return nullptr;
}

void IocRelation::getListImpl(BaseEntity::SPtr entity,
                              std::vector<Int>::const_iterator iter,
                              const std::vector<Int>& signs) {
  if (iter == signs.end()) {
    tl_ref_dynamic2.add(entity);
  } else {
    IList::Iterator relaIter = entity->_relations[*iter++]->iterator();
    while (relaIter.hasNext()) {
      getListImpl(relaIter.next<BaseEntity>(), iter, signs);
    }
  }
}

BaseEntity::SPtr IocRelation::get(BaseEntity::SPtr entity, Int sign) {
  return entity->_relations[sign]->get();
}

BaseEntity::SPtr IocRelation::get(BaseEntity::SPtr entity,
                                    const std::vector<Int>& signs) {
  return getImpl(entity, signs.begin(), signs);
}

const IList& IocRelation::getList(BaseEntity::SPtr entity, Int sign) {
  return *entity->_relations[sign];
}

const IList& IocRelation::getList(BaseEntity::SPtr entity,
                                  const std::vector<Int>& signs) {
  tl_ref_dynamic2.remove();
  getListImpl(entity, signs.begin(), signs);
  return tl_ref_dynamic2;
}

void IocRelation::set(BaseEntity::SPtr entity, Int sign,
                      BaseEntity::SPtr relaEntity) {
  if (!entity.valid() || !relaEntity.valid()) {
    return;
  }

  const EntityFactory::Data* data =
      FactoryMgr::instance().getRelaData(entity->getClass(), sign);
  switch (data->rela) {
    case EntityFactory::Relation::OneToOne:
      remove(entity, sign);
      remove(relaEntity, data->relaSign);
      break;
    case EntityFactory::Relation::OneToMulti:
      remove(relaEntity, data->relaSign);
      break;
    case EntityFactory::Relation::MultiToOne:
      remove(entity, sign);
      break;
    case EntityFactory::Relation::MultiToMulti:
      break;
    default:
      break;
  }

  entity->_relations[sign]->add(relaEntity);
  if (data->relaSign > 0) {
    relaEntity->_relations[data->relaSign]->add(entity);
  }
}

void IocRelation::remove(BaseEntity::SPtr entity, Int sign) {
  const EntityFactory::Data* data =
      FactoryMgr::instance().getRelaData(entity->getClass(), sign);
  if (data != nullptr && data->relaSign > 0) {
    const IList& relaEntities = *(entity->_relations[sign]);
    IList::Iterator iter = relaEntities.iterator();
    while (iter.hasNext()) {
      BaseEntity::SPtr relaEntity = iter.next<BaseEntity>();
      relaEntity->_relations[data->relaSign]->remove(entity);
    }
  }

  entity->_relations[sign]->remove();
}

void IocRelation::remove(BaseEntity::SPtr entity, Int sign,
                         BaseEntity::SPtr relaEntity) {
  const EntityFactory::Data* data =
      FactoryMgr::instance().getRelaData(entity->getClass(), sign);
  if (data != nullptr && data->relaSign > 0) {
    relaEntity->_relations[data->relaSign]->remove(entity);
  }

  entity->_relations[sign]->remove(relaEntity);
}

}  // namespace gemini