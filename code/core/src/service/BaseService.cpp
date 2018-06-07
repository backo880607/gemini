#include "service/BaseService.h"
#include "service/ServiceMgr.h"
#include "dao/Memory.h"
#include "entities/IocRelation.h"

namespace gemini
{

EntityObject::SPtr BaseService::createImpl(const Class &cls, Long id) const
{
	return Memory::create(cls, id);
}

EntityObject::SPtr BaseService::createTempImpl(const Class &cls) const
{
	return Memory::createTemp(cls);
}

EntityObject::SPtr BaseService::getImpl(const Class &cls) const
{
	return Memory::get(cls);
}

EntityObject::SPtr BaseService::getImpl(const Class &cls, Long id) const
{
	return Memory::get(cls, id);
}

EntityObject::SPtr BaseService::getInheritImpl(const Class &cls, Long id) const
{
	return EntityObject::SPtr();
}

static RefVector ddddddd = RefVector();
const IList &BaseService::getListImpl(const Class &cls) const
{
	return ddddddd;
	//return Memory::getList(cls);
}

EntityObject::SPtr BaseService::getImpl(EntityObject::SPtr entity, const std::vector<Int> &signs) const
{
	return IocRelation::get(entity, signs);
}

const IList &BaseService::getListImpl(EntityObject::SPtr entity, const std::vector<Int> &signs) const
{
	return IocRelation::getList(entity, signs);
}

void BaseService::setImpl(EntityObject::SPtr entity, Int sign, EntityObject::SPtr relaEntity) const
{
	IocRelation::set(entity, sign, relaEntity);
}

void gemini_afx_service_service(const String &name, const BaseService *service)
{
	ServiceMgr::instance().registerService(name, service);
}

const IBaseService *gemini_afx_service_interface_get(const String &iName)
{
	return ServiceMgr::instance().getInterface(iName);
}

void gemini_afx_service_interface(const String &name, const IBaseService *service)
{
	ServiceMgr::instance().registerInterface(name, service);
}

ServiceAutowired::ServiceAutowired(const String &iName)
{
	ServiceMgr::instance().registerAutowired(this, iName);
}

namespace service
{

void register_service_method_impl(const String &name, const String &method, callable *caller)
{
	ServiceMgr::instance().registerServiceMethod(name, method, caller);
}

} // namespace service
} // namespace gemini