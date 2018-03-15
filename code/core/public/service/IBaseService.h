#ifndef GEMINI_IBaseService_INCLUDE
#define GEMINI_IBaseService_INCLUDE
#include "../Object.h"

namespace gemini {

class CORE_API IBaseService
{
	IBaseService(const IBaseService&) = delete;
	IBaseService operator= (const IBaseService&) = delete;
protected:
	IBaseService() {}
	virtual ~IBaseService() {}
};

extern CORE_API const IBaseService* gemini_afx_service_interface_get(const String& iName);
template <class T>
class ServiceHelper
{
public:
	ServiceHelper() {
		_service = (const T*)gemini_afx_service_interface_get(Class::getName<T>());
	}
	~ServiceHelper() {}

	const T* operator-> () const { return _service; }
private:
	const T* _service;
};

}
#endif // GEMINI_IBaseService_INCLUDE