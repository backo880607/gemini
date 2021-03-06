#ifndef GEMINI_ServiceMgr_INCLUDE
#define GEMINI_ServiceMgr_INCLUDE
#include "../../public/service/BaseService.h"

namespace gemini {

class ServiceMgr final : public noncopyable
{
	struct Data {
		const BaseService* _service;
		std::map<String, service::callable*> _callers;
	};

	ServiceMgr();
public:
	~ServiceMgr();
	static ServiceMgr& instance() { static ServiceMgr mgr; return mgr; }

	void init();

	void registerService(const String& name, const BaseService* service);
	void registerInterface(const String& name, const IBaseService* service);
	void registerAutowired(ServiceAutowired* service, const String& iName);
	void registerServiceMethod(const String& srvName, const String& method, service::callable* caller);

	const BaseService* get(const String& name) const;
	const IBaseService* getInterface(const String& iName) const;

	service::callable* getCallers(const String& srvName, const String& methodName);

private:
	std::map<String, Data> _services;
	std::map<String, const IBaseService*> _interfaces;
	std::map<ServiceAutowired*, String> _autowireds;
};

}
#endif // GEMINI_ServiceMgr_INCLUDE
