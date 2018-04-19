#include "tools/LocaleUtil.h"

namespace gemini {

std::ostringstream& LocaleUtil::getOSS(Boolean bReset /* = false */)
{
	if (bReset) {
		_ssout.clear();
		_ssout.str(u8"");
	}
	return _ssout;
}

std::istringstream& LocaleUtil::getISS(const Char* str /* = nullptr */)
{
	if (str != nullptr) {
		_ssin.clear();
		_ssin.str(str);
	}
	return _ssin;
}

void LocaleUtil::setLocale(const std::locale& loc)
{
	_locale = loc;
	_ssout.imbue(_locale);
	_ssin.imbue(_locale);
}

}