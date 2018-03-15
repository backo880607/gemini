#include "../../public/tools/StringUtil.h"
#include "../../public/Any.h"
#include "../../public/DateTime.h"
#include "../../public/session/Subject.h"
#include "../../include/tools/LocaleUtil.h"
#include "../../include/Application.h"

#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace gemini {

void StringUtil::to_upper(String& str)
{
	boost::to_upper(str, g_app.getLocale());
}

void StringUtil::to_lower(String& str)
{
	return boost::to_lower(str, g_app.getLocale());
}

void StringUtil::trim_lift(String& str)
{
	boost::trim_left(str, g_app.getLocale());
}

void StringUtil::trim_right(String& str)
{
	boost::trim_right(str, g_app.getLocale());
}

void StringUtil::trim(String& str)
{
	boost::trim(str, g_app.getLocale());
}

Boolean StringUtil::starts_with(const Char* str, const Char* test)
{
	return boost::starts_with(str, test);
}

Boolean StringUtil::istarts_with(const Char * str, const Char * test)
{
	return boost::istarts_with(str, test, g_app.getLocale());
}

Boolean StringUtil::ends_with(const Char* str, const Char* test)
{
	return boost::ends_with(str, test);
}

Boolean StringUtil::iends_with(const Char * str, const Char * test)
{
	return boost::iends_with(str, test, g_app.getLocale());
}

Boolean StringUtil::contains(const Char * str, const Char * test)
{
	return boost::contains(str, test);
}

Boolean StringUtil::icontains(const Char * str, const Char * test)
{
	return boost::icontains(str, test, g_app.getLocale());
}

Boolean StringUtil::equals(const Char* str, const Char* test)
{
	return boost::equals(str, test);
}

Boolean StringUtil::iequals(const Char * str, const Char * test)
{
	return boost::iequals(str, test, g_app.getLocale());
}

Int StringUtil::compare(const Char * str, const Char * test)
{
	return boost::lexicographical_compare(str, test);
}

Int StringUtil::icompare(const Char * str, const Char * test)
{
	return Int();
}

String StringUtil::find_last(const String& str, const Char* sep)
{
	const String::size_type pos = str.find_last_of(sep);
	return pos != String::npos ? str.substr(pos + strlen(sep)) : "";
}

const Char* StringUtil::increment(const Char* str)
{
	while (*++str != '\0') {
		if (*str & 0xc0 != 0x80) {
			break;
		}
	}

	return str;
}

const Char* StringUtil::descending(const Char* str)
{
	while (--str) {
		if (*str & 0xc0 != 0x80) {
			break;
		}
	}

	return str;
}

Int StringUtil::icompare(const String & str, const Char * rhs)
{
	Char f, l;
	const Char * dst = str.c_str();
	const Char * src = rhs;
	do
	{
		f = std::tolower(*dst, g_app.getLocale());
		l = std::tolower(*src, g_app.getLocale());
		dst++;
		src++;
	} while ((f) && (f == l));
	return (Int)(f - l);
}

void StringUtil::replace(String& str, const Char* origin, const Char* des)
{
	String::size_type lastpos = 0, thispos;
	const String::size_type lLen = strlen(origin);
	const String::size_type rLen = strlen(des);
	while ((thispos = str.find(origin, lastpos)) != String::npos)
	{
		str.replace(thispos, lLen, des);
		lastpos = thispos + rLen;
	}
}

std::wstring StringUtil::utf8_to_unicode(const Char * src)
{
	return boost::locale::conv::to_utf<wchar_t>(src, "UTF-8");
}

String StringUtil::uuid()
{
	boost::uuids::random_generator gen;
	boost::uuids::uuid u = gen();
	return boost::uuids::to_string(u);
}

std::ostringstream& getStream() {
	return Subject::get().getSession()->get<LocaleUtil>().getOSS();
}
String StringUtil::formatImpl(Boolean val)
{
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(Short val)
{
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(UShort val)
{
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(Int val)
{
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(UInt val)
{
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(Long val)
{
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(ULong val)
{
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(Float val) {
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(Double val) {
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(LDouble val) {
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::number << val;
	return ss.str();
}
String StringUtil::formatImpl(Char val) {
	return String(1, val);
}
String StringUtil::formatImpl(UChar val)
{
	return String(1, val);
}
String StringUtil::formatImpl(WChar val) {
	//return val;
	return "";
}
String StringUtil::formatImpl(Char16 val) {
	//return val;
	return "";
}
String StringUtil::formatImpl(Char32 val) {
	//return val;
	return "";
}
String StringUtil::formatImpl(WChar* val)
{
	return boost::locale::conv::utf_to_utf<Char>(val);
}
String StringUtil::formatImpl(const WChar* val) {
	return boost::locale::conv::utf_to_utf<Char>(val);
}
String StringUtil::formatImpl(const Any& val)
{
	return val.str();
}

String StringUtil::formatImpl(const DateTime& val)
{
	std::ostringstream& ss = getStream();
	ss << boost::locale::as::datetime << boost::locale::as::local_time << val.getTime();
	return ss.str();
}

String StringUtil::format(Float val, Int precision) {
	return "";
}

String StringUtil::format(Double val, Int precision) {
	return "";
}

String StringUtil::format(LDouble val, Int precision) {
	return "";
}

String StringUtil::format(const DateTime& val, const Char* f)
{
	tm* t1 = localtime(&val._time);
	Char temp[128];
	strftime(temp, 128, f, t1);
	return temp;
}

Long StringUtil::convertLong(const Char* str, std::size_t fPos /*= 0*/, std::size_t lPos /*= npos*/)
{
	if (str == nullptr || fPos >= lPos)
		return 0;

	Long number = 0;
	const Char* p = str + fPos;
	const Char* pEnd = lPos == String::npos ? nullptr : str + lPos;
	Char c = *p++;
	int flags = 0;

	while (iswspace(c))
		c = *p++;       /* skip whitespace */

	if (c == '-') {
		flags = 1;
		c = *p++;
	}
	else if (c == '+')
		c = *p++;       /* skip sign */

	Long maxval = Long_MAX / 10;

	unsigned digval;
	for (;;) {
		if ((digval = (c - L'0')) >= 10)
		{
			assert(c == L'\0');
			break;
		}

		if (number < maxval || (number == maxval &&
			(unsigned long)digval <= Long_MAX % 10)) {
			/* we won't overflow, go ahead and multiply */
			number = number * 10 + digval;
		}
		else {
			number = 0;
			break;
		}

		if (p == pEnd)
			break;

		c = *p++;       /* read next digit */
	}

	return (flags == 1 ? -(Long)number : number);
}
}