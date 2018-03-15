#ifndef GEMINI_IApplication_INCLUDE
#define GEMINI_IApplication_INCLUDE
#include "Common.h"

namespace gemini {

class CORE_API IApplication
{
public:
	virtual void init() = 0;

	virtual const Char* getConfigPath() = 0;

	virtual const std::locale& getLocale() = 0;
	virtual void setLocale(const Char* name) = 0;
};
CORE_API IApplication& getApp();

}
#endif // GEMINI_IApplication_INCLUDE