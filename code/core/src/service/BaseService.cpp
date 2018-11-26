#include "service/BaseService.h"
#include "service/IBaseService.h"
#include "service/ServiceMgr.h"

namespace gemini {

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