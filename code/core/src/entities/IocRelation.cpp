#include "entities/IocRelation.h"
#include "entities/RefVector.h"
#include "entities/EntityFactory.h"
#include "entities/FactoryMgr.h"

namespace gemini {

thread_local RefVector tl_ref_dynamic2;
EntityObject::SPtr IocRelation::getImpl(EntityObject::SPtr entity, std::vector<Int>::const_iterator iter, const std::vector<Int>& signs)
{
	if (iter == signs.end()) {
		return entity;
	} else {
		IList::Iterator relaIter = entity->_relations[*iter++]->iterator();
		while (relaIter.hasNext()) {
			EntityObject::SPtr result = getImpl(relaIter.next<EntityObject>(), iter, signs);
			if (result.valid()) {
				return result;
			}
		}
	}

	return nullptr;
}

void IocRelation::getListImpl(EntityObject::SPtr entity, std::vector<Int>::const_iterator iter, const std::vector<Int>& signs)
{
	if (iter == signs.end()) {
		tl_ref_dynamic2.add(entity);
	} else {
		IList::Iterator relaIter = entity->_relations[*iter++]->iterator();
		while (relaIter.hasNext()) {
			getListImpl(relaIter.next<EntityObject>(), iter, signs);
		}
	}
}

EntityObject::SPtr IocRelation::get(EntityObject::SPtr entity, Int sign)
{
	return entity->_relations[sign]->get();
}

EntityObject::SPtr IocRelation::get(EntityObject::SPtr entity, const std::vector<Int>& signs)
{
	return getImpl(entity, signs.begin(), signs);
}

const IList& IocRelation::getList(EntityObject::SPtr entity, Int sign)
{
	return *entity->_relations[sign];
}

const IList& IocRelation::getList(EntityObject::SPtr entity, const std::vector<Int>& signs)
{
	tl_ref_dynamic2.remove();
	getListImpl(entity, signs.begin(), signs);
	return tl_ref_dynamic2;
}

void IocRelation::set(EntityObject::SPtr entity, Int sign, EntityObject::SPtr relaEntity)
{
	if (!entity.valid() || !relaEntity.valid()) {
		return;
	}

	const EntityFactory::Data* data = FactoryMgr::instance().getRelaData(entity->getClass(), sign);
	switch (data->rela)
	{
	case EntityFactory::Relation::OneToOne:
		remove(entity, sign);
		remove(relaEntity, data->reverseSign);
		break;
	case EntityFactory::Relation::OneToMulti:
		remove(relaEntity, data->reverseSign);
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
	if (data->reverseSign > 0) {
		relaEntity->_relations[data->reverseSign]->add(entity);
	}
}

void IocRelation::remove(EntityObject::SPtr entity, Int sign)
{
	const EntityFactory::Data* data = FactoryMgr::instance().getRelaData(entity->getClass(), sign);
	if (data != nullptr && data->reverseSign > 0) {
		const IList& relaEntities = *(entity->_relations[sign]);
		IList::Iterator iter = relaEntities.iterator();
		while (iter.hasNext())
		{
			EntityObject::SPtr relaEntity = iter.next<EntityObject>();
			relaEntity->_relations[data->reverseSign]->remove(entity);
		}
	}

	entity->_relations[sign]->remove();
}

void IocRelation::remove(EntityObject::SPtr entity, Int sign, EntityObject::SPtr relaEntity)
{
	const EntityFactory::Data* data = FactoryMgr::instance().getRelaData(entity->getClass(), sign);
	if (data != nullptr && data->reverseSign > 0) {
		relaEntity->_relations[data->reverseSign]->remove(entity);
	}

	entity->_relations[sign]->remove(relaEntity);
}

}