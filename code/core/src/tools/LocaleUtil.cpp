#include "../../include/tools/LocaleUtil.h"

namespace gemini {

std::ostringstream& LocaleUtil::getOSS()
{
	_ssout.str(u8"");
	return _ssout;
}

std::istringstream& LocaleUtil::getISS()
{
	return _ssin;
}

void LocaleUtil::setLocale(const std::locale& loc)
{
	_locale = loc;
	_ssout.imbue(_locale);
	_ssin.imbue(_locale);
}

}