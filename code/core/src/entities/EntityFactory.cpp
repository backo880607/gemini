#include "entities/EntityFactory.h"
#include "entities/RefEntity.h"
#include "entities/RefList.h"
#include "entities/RefSet.h"
#include "entities/RefVector.h"

namespace gemini {

EntityFactory::EntityFactory(const Class& cls) 
	: _cls(cls)
{
	if (cls != EntityObject::getClassStatic()) {
		_all.wrapRawPointer((EntityObject*)_cls.newInstance());
		cls.foreach_fields([&](const Field* field) {
			if (field->index() > 0) {
				EntityFactory::Data& data = _relations[field->index()];
				data.sign = field->index();
				data.name = field->getName();
			}
		});
	}
}

EntityFactory::~EntityFactory()
{

}

UInt EntityFactory::getRelaSign(const String& signName) const
{
	for (auto iter : _relations) {
		const Data& relaData = iter.second;
		if (relaData.name == signName) {
			return iter.first;
		}
	}

	return _super != nullptr ? _super->getRelaSign(signName) : 0;
}

const EntityFactory::Data* EntityFactory::getRelaData(UInt sign) const
{
	auto iter = _relations.find(sign);
	if (iter != _relations.end()) {
		return &iter->second;
	}

	return _super != nullptr ? _super->getRelaData(sign) : nullptr;
}

const EntityFactory::Data* EntityFactory::getRelaData(const String& signName) const
{
	return getRelaData(getRelaSign(signName));
}

void EntityFactory::createRelation(const EntityObject::SPtr & entity)
{
	if (entity->_relations.empty()) {
		entity->_relations.resize(entity->signMaxIndex());
	}
	for (auto iter = _relations.begin(); iter != _relations.end(); ++iter) {
		RefBase* ref = nullptr;
		switch (iter->second.type) {
		case EntityFactory::RefType::T_Singleton:
			ref = new RefEntity();
			break;
		case EntityFactory::RefType::T_List:
			ref = new RefVector();
			break;
		case EntityFactory::RefType::T_Set:
			break;
		case EntityFactory::RefType::T_Sequence:
			ref = new RefList();
			break;
		default:
			break;
		}
		entity->_relations[iter->first] = ref;
	}

	if (_super != nullptr) {
		_super->createRelation(entity);
	}
}

}