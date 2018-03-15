#include "../../include/Entities/IocRelation.h"
#include "../../include/Entities/RefVector.h"
#include "../../include/Entities/EntityFactory.h"
#include "../../include/Entities/FactoryMgr.h"

namespace gemini {

EntityObject::SPtr IocRelation::getImpl(EntityObject::SPtr entity, std::vector<UInt>::const_iterator iter, const std::vector<UInt>& signs)
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

void IocRelation::getListImpl(EntityObject::SPtr entity, std::vector<UInt>::const_iterator iter, const std::vector<UInt>& signs, std::vector<EntityObject::SPtr>& result)
{
	if (iter == signs.end()) {
		result.push_back(entity);
	} else {
		IList::Iterator relaIter = entity->_relations[*iter++]->iterator();
		while (relaIter.hasNext()) {
			getListImpl(relaIter.next<EntityObject>(), iter, signs, result);
		}
	}
}

EntityObject::SPtr IocRelation::get(EntityObject::SPtr entity, UInt sign)
{
	return entity->_relations[sign]->get();
}

EntityObject::SPtr IocRelation::get(EntityObject::SPtr entity, const std::vector<UInt>& signs)
{
	return getImpl(entity, signs.begin(), signs);
}

const RefBase* IocRelation::getList(EntityObject::SPtr entity, UInt sign)
{
	return entity->_relations[sign];
}

std::vector<EntityObject::SPtr> IocRelation::getList(EntityObject::SPtr entity, const std::vector<UInt>& signs)
{
	std::vector<EntityObject::SPtr> result;
	getListImpl(entity, signs.begin(), signs, result);
	return result;
}

void IocRelation::set(EntityObject::SPtr entity, UInt sign, EntityObject::SPtr relaEntity)
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

void IocRelation::remove(EntityObject::SPtr entity, UInt sign)
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

void IocRelation::remove(EntityObject::SPtr entity, UInt sign, EntityObject::SPtr relaEntity)
{
	const EntityFactory::Data* data = FactoryMgr::instance().getRelaData(entity->getClass(), sign);
	if (data != nullptr && data->reverseSign > 0) {
		relaEntity->_relations[data->reverseSign]->remove(entity);
	}

	entity->_relations[sign]->remove(relaEntity);
}

}