#include "Object.h"
#include "entities/FactoryHelper.h"
#include "entities/FactoryMgr.h"
#include "message/Exception.h"

namespace gemini {

FactoryMgr::FactoryMgr() : _factories(Class::max_limits()) {}

void FactoryMgr::init() {
  const std::map<String, const Class* const>& clses = geminiAfxEntityClasses();
  for (auto iter : clses) {
    const Class& cls = *iter.second;
    if (!cls.isBase(BaseEntity::getClassStatic())) {
      continue;
    }

    EntityFactory* factory = new EntityFactory(cls);
    _factories[cls.index()] = factory;
    _factoryNames.insert(std::make_pair(cls.getName(), factory));
  }

  for (auto iter : clses) {
    const Class& cls = *iter.second;
    if (!cls.isBase(BaseEntity::getClassStatic()) || !cls.hasSuper()) {
      continue;
    }

    const Class& superCls = cls.getSuperClass();
    if (superCls == BaseEntity::getClassStatic()) {
      continue;
    }

    EntityFactory* factory = getFactory(cls);
    EntityFactory* superFactory = getFactory(superCls);
    if (factory != nullptr && superFactory != nullptr) {
      factory->_super = superFactory;
      superFactory->_childs.push_back(factory);
    }
  }

  // FactoryHelper helper;
  // helper.loadConfig();
}

void FactoryMgr::unInit() {
  _factoryNames.clear();
  for (EntityFactory* factory : _factories) {
    delete factory;
  }
  _factories.clear();
}

EntityFactory* FactoryMgr::getFactory(const Class& cls) const {
  if ((std::size_t)cls.index() >= _factories.size()) {
    return nullptr;
  }

  return _factories[cls.index()];
}

EntityFactory* FactoryMgr::getFactory(const String& name) const {
  std::map<String, EntityFactory*>::const_iterator iter =
      _factoryNames.find(name);
  return iter != _factoryNames.end() ? iter->second : nullptr;
}

const EntityFactory::Data* FactoryMgr::getRelaData(const Class& cls,
                                                   Int sign) const {
  EntityFactory* factory = getFactory(cls);
  return factory != nullptr ? factory->getRelaData(sign) : nullptr;
}

const EntityFactory::Data* FactoryMgr::getRelaData(
    const Class& cls, const String& sign) const {
  EntityFactory* factory = getFactory(cls);
  return factory != nullptr ? factory->getRelaData(sign) : nullptr;
}

Boolean FactoryMgr::isFieldStoraged(const Class& cls,
                                    const Field& field) const {
  const EntityFactory::Data* data = getRelaData(cls, field.index());
  THROW_IF(data == nullptr, NoSuchElementException, cls.getName(), ": ",
           field.getName());
  return data->storage;
}

}  // namespace gemini