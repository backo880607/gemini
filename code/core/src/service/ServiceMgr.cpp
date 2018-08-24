#include "message/Exception.h"
#include "service/ServiceMgr.h"

namespace gemini {

ServiceMgr::ServiceMgr() {}

ServiceMgr::~ServiceMgr() {}

void ServiceMgr::init() {
  for (std::map<ServiceAutowired*, String>::iterator iter = _autowireds.begin();
       iter != _autowireds.end(); ++iter) {
    const void* service = getInterface(iter->second).get();
    THROW_IF(service == nullptr, Exception,
             u8"not register service interface: ", iter->second)
    iter->first->assign(service);
  }
}

void ServiceMgr::registerService(const String& name,
                                 const BaseService* service) {
  std::map<String, Data>::iterator iter = _services.find(name);
  THROW_IF(iter != _services.end() && iter->second._service != nullptr,
           Exception, u8"repeat register service: ", name)
  _services[name]._service = service;
}

void ServiceMgr::registerInterface(const String& name,
                                   const service::Wrap& service) {
  std::map<String, service::Wrap>::iterator iter = _interfaces.find(name);
  THROW_IF(iter != _interfaces.end(), Exception,
           u8"repeat register service interface: ", name)
  _interfaces.insert(std::make_pair(name, service));
}

const BaseService* ServiceMgr::get(const String& name) const {
  std::map<String, Data>::const_iterator iter = _services.find(name);
  return iter != _services.end() ? iter->second._service : nullptr;
}

service::Wrap ServiceMgr::getInterface(const String& iName) const {
  std::map<String, service::Wrap>::const_iterator iter =
      _interfaces.find(iName);
  return iter != _interfaces.end() ? iter->second : nullptr;
}

service::callable* ServiceMgr::getCallers(const String& srvName,
                                          const String& methodName) {
  std::map<String, Data>::const_iterator iter = _services.find(srvName);
  if (iter == _services.end()) {
    return nullptr;
  }

  std::map<String, service::callable*>::const_iterator dataIter =
      iter->second._callers.find(methodName);
  return dataIter != iter->second._callers.end() ? dataIter->second : nullptr;
}

void ServiceMgr::registerAutowired(ServiceAutowired* service,
                                   const String& iName) {
  _autowireds[service] = iName;
}

void ServiceMgr::registerServiceMethod(const String& srvName,
                                       const String& method,
                                       service::callable* caller) {
  _services[srvName]._callers.insert(std::make_pair(method, caller));
}

}  // namespace gemini