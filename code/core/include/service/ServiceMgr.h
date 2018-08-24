#ifndef GEMINI_ServiceMgr_INCLUDE
#define GEMINI_ServiceMgr_INCLUDE
#include "../../public/service/BaseService.h"

namespace gemini {

class ServiceMgr final : public noncopyable {
  struct Data {
    const BaseService *_service = nullptr;
    std::map<String, service::callable *> _callers;
  };

  ServiceMgr();

 public:
  ~ServiceMgr();
  static ServiceMgr &instance() {
    static ServiceMgr mgr;
    return mgr;
  }

  void init();

  void registerService(const String &name, const BaseService *service);
  void registerInterface(const String &name, const service::Wrap &service);
  void registerAutowired(ServiceAutowired *service, const String &iName);
  void registerServiceMethod(const String &srvName, const String &method,
                             service::callable *caller);

  const BaseService *get(const String &name) const;
  const BaseService *get(const Class &cls) const { return get(cls.getName()); }
  service::Wrap getInterface(const String &iName) const;

  service::callable *getCallers(const String &srvName,
                                const String &methodName);

 private:
  std::map<String, Data> _services;
  std::map<String, service::Wrap> _interfaces;
  std::map<ServiceAutowired *, String> _autowireds;
};

}  // namespace gemini
#endif  // GEMINI_ServiceMgr_INCLUDE