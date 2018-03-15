#include "../../public/service/BaseService.h"
#include "../../include/service/ServiceMgr.h"
#include "../../include/cache/Cache.h"
#include "../../include/entities/IocRelation.h"

namespace gemini {

EntityObject::SPtr BaseService::createImpl(const Class& cls, Long id) const
{
	return Cache::create(cls, id);
}

EntityObject::SPtr BaseService::getImpl(const Class& cls) const
{
	return Cache::get(cls);
}

EntityObject::SPtr BaseService::getImpl(const Class & cls, Long id) const
{
	return Cache::get(cls, id);
}

EntityObject::SPtr BaseService::getInheritImpl(const Class & cls, Long id) const
{
	return EntityObject::SPtr();
}

std::vector<EntityObject::SPtr> BaseService::getListImpl(const Class & cls) const
{
	return Cache::getList(cls);
}

EntityObject::SPtr BaseService::getImpl(EntityObject::SPtr entity, const std::vector<UInt>& signs) const
{
	return IocRelation::get(entity, signs);
}

std::vector<EntityObject::SPtr> BaseService::getListImpl(EntityObject::SPtr entity, const std::vector<UInt>& signs) const
{
	return IocRelation::getList(entity, signs);
}

void gemini_afx_service_service(const String& name, const BaseService* service)
{
	ServiceMgr::instance().registerService(name, service);
}

const IBaseService* gemini_afx_service_interface_get(const String& iName)
{
	return ServiceMgr::instance().getInterface(iName);
}

void gemini_afx_service_interface(const String& name, const IBaseService* service)
{
	ServiceMgr::instance().registerInterface(name, service);
}

ServiceAutowired::ServiceAutowired(const String& iName)
{
	ServiceMgr::instance().registerAutowired(this, iName);
}

namespace service {

void register_service_method_impl(const String& name, const String& method, callable* caller)
{
	ServiceMgr::instance().registerServiceMethod(name, method, caller);
}

}
}