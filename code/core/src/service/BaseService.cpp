#include "dao/Memory.h"
#include "entities/IocRelation.h"
#include "service/BaseService.h"
#include "service/IBaseService.h"
#include "service/ServiceMgr.h"

namespace gemini {

EntityObject::SPtr BaseService::createImpl(const Class &cls, Long id) const {
  return Memory::create(cls, id);
}

EntityObject::SPtr BaseService::createTempImpl(const Class &cls) const {
  return Memory::createTemp(cls);
}

EntityObject::SPtr BaseService::getImpl(const Class &cls) const {
  return Memory::get(cls);
}

EntityObject::SPtr BaseService::getImpl(const Class &cls, Long id) const {
  return Memory::get(cls, id);
}

EntityObject::SPtr BaseService::getInheritImpl(const Class &cls,
                                               Long id) const {
  EntityObject::SPtr entity = getImpl(cls, id);
  if (entity.valid()) {
    return entity;
  }

  return nullptr;
}

thread_local RefVector ddddddd = RefVector();
const IList &BaseService::getListImpl(const Class &cls) const {
  return Memory::getList(cls);
}

void BaseService::eraseImpl(EntityObject::SPtr entity) const {
  Memory::erase(entity->getClass(), entity->getID());
}

void BaseService::clearImpl(const Class &cls) const { Memory::clear(cls); }

EntityObject::SPtr BaseService::getImpl(EntityObject::SPtr entity,
                                        const std::vector<Int> &signs) const {
  return IocRelation::get(entity, signs);
}

const IList &BaseService::getListImpl(EntityObject::SPtr entity,
                                      const std::vector<Int> &signs) const {
  return IocRelation::getList(entity, signs);
}

void BaseService::setImpl(EntityObject::SPtr entity, Int sign,
                          EntityObject::SPtr relaEntity) const {
  IocRelation::set(entity, sign, relaEntity);
}

void BaseService::removeImpl(EntityObject::SPtr entity, Int sign) const {
  IocRelation::remove(entity, sign);
}

void BaseService::removeImpl(EntityObject::SPtr entity, Int sign,
                             EntityObject::SPtr relaEntity) const {
  IocRelation::remove(entity, sign, relaEntity);
}

void BaseService::sync() const { Memory::sync(); }

namespace service {

void register_service(const String &name, const BaseService *service) {
  ServiceMgr::instance().registerService(name, service);
}

void register_interface(const String &name, const Wrap &service) {
  ServiceMgr::instance().registerInterface(name, service);
}

Wrap get_service_interface(const String &iName) {
  return ServiceMgr::instance().getInterface(iName);
}

}  // namespace service

ServiceAutowired::ServiceAutowired(const String &iName) {
  ServiceMgr::instance().registerAutowired(this, iName);
}

namespace service {

void register_service_method_impl(const String &name, const String &method,
                                  callable *caller) {
  ServiceMgr::instance().registerServiceMethod(name, method, caller);
}

}  // namespace service
}  // namespace gemini