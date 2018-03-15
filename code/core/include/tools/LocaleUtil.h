#ifndef GEMINI_LocaleUtil_INCLUDE
#define GEMINI_LocaleUtil_INCLUDE
#include "../../public/Common.h"

#include <boost/locale.hpp>

namespace gemini {

class LocaleUtil final : public noncopyable
{
public:
	std::ostringstream& getOSS();

	std::istringstream& getISS();

	const std::locale& getLocale() const { return _locale; }
	void setLocale(const std::locale& loc);

private:
	std::locale _locale;
	std::ostringstream _ssout;
	std::istringstream _ssin;
};

}
#endif // GEMINI_LocaleUtil_INCLUDE
