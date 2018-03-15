#ifndef GEMINI_StringUtil_INCLUDE
#define GEMINI_StringUtil_INCLUDE
#include "../Common.h"

namespace gemini {
	
class Any;
class DateTime;
class CORE_API StringUtil final : public noncopyable
{
	StringUtil() = delete;
	StringUtil(const StringUtil&) = delete;
	StringUtil& operator=(const StringUtil&) = delete;
public:
	static void to_upper(String& str);
	static void to_lower(String& str);

	static void trim_lift(String& str);
	static void trim_right(String& str);
	static void trim(String& str);

	static Boolean starts_with(const Char* str, const Char* test);
	static Boolean istarts_with(const Char* str, const Char* test);
	static Boolean ends_with(const Char* str, const Char* test);
	static Boolean iends_with(const Char* str, const Char* test);
	static Boolean contains(const Char* str, const Char* test);
	static Boolean icontains(const Char* str, const Char* test);
	static Boolean equals(const Char* str, const Char* test);
	static Boolean iequals(const Char* str, const Char* test);
	static Int compare(const Char* str, const Char* test);
	static Int icompare(const Char* str, const Char* test);


	static String find_last(const String& str, const Char* sep);

	static const Char* increment(const Char* str);
	static const Char* descending(const Char* str);

	static Int icompare(const String& str, const Char* rhs);

	template <typename T>
	static String format(T val) { return formatImpl(val); }
	static String format(Float val, Int precision);
	static String format(Double val, Int precision);
	static String format(LDouble val, Int precision);
	static String format(const DateTime& val, const Char* f);

	template <typename T>
	static T convert(const Char* str) { 
		std::remove_const<T>::type val;
		convertImpl(val, str);
		if (errno == ERANGE) {

		}

		return val;
	}
	template <typename T>
	static T convert(const Char* str, std::size_t fPos, std::size_t lPos) {
		return (T)convertLong(str, fPos, lPos);
	}
	template <>
	static String convert<String>(const Char* str, std::size_t fPos, std::size_t lPos) {
		return String(str + fPos, lPos - fPos);
	}

	static void append(String& str) {}
	template <typename T, typename ...Args>
	static void append(String& str, T val, Args... args) {
		str.append(format(val));
		append(str, args);
	}

	template <typename T>
	static String join(const T& container, const Char* sep, Boolean bPair = false) {
		typename T::const_iterator fIter = container.begin();
		typename T::const_iterator lIter = container.end();
		return std::move(join(fIter, lIter, sep, bPair));
	}

	template <typename InputIter>
	static String join(InputIter fIter, InputIter lIter, const Char* sep, Boolean bPair = false) {
		String value;
		for (; fIter != lIter; ++fIter) {
			value += format(*fIter) += sep;
		}
		if (false == bPair && !value.empty()) {
			value.erase(value.size() - strlen(sep));
		}

		return std::move(value);
	}

	template <typename T>
	static void parse(std::vector<T>& vecVal, const String& str, const Char* sep, std::size_t fPos = 0, std::size_t lPos = String::npos) {
 		if (fPos >= lPos || str.empty()) return;
 
 		const std::size_t sepLen = strlen(sep);
		std::size_t idx = str.find(sep, fPos);
 		while (idx != String::npos && idx < lPos) {
 			vecVal.push_back(convert<T>(str.c_str(), fPos, idx));
 			idx += sepLen;
 			fPos = idx;
 			idx = str.find(sep, idx);
 		}
 
 		if (fPos <= lPos)
 			vecVal.push_back(convert<T>(str.c_str(), fPos, lPos));
	}

	template <typename T, typename Fun>
	static void parse(const String& str, const Char* sep, Fun fun, std::size_t fPos = 0, std::size_t lPos = String::npos) {
		if (fPos >= lPos || str.empty()) return;

		const std::size_t sepLen = strlen(sep);
		std::size_t idx = str.find(sep, fPos);
		while (idx != String::npos && idx < lPos)
		{
			fun(convert<T>(str.c_str(), fPos, idx));
			idx += sepLen;
			fPos = idx;
			idx = str.find(sep, idx);
		}

		if (fPos <= lPos)
		{
			fun(convert<T>(str.c_str(), fPos, lPos));
		}
	}
	template <typename T, typename Fun>
	static void parse(const String& str, const Char* sep, Fun fun, const Char* lhs, const Char* rhs) {
		std::size_t fPos = str.find(lhs);
		if (fPos != String::npos)
		{
			std::size_t lPos = str.find(rhs, ++fPos);
			if (lPos != String::npos)
				parse<T>(str, sep, fun, fPos, lPos);
		}
	}

	static void replace(String& str, const Char* origin, const Char* des);

	static std::wstring utf8_to_unicode(const Char* src);

	static String uuid();
private:
	template <typename T>
	static String formatImpl(const T& val) { return val.str(); }
	static String formatImpl(Boolean val);
	static String formatImpl(Short val);
	static String formatImpl(UShort val);
	static String formatImpl(Int val);
	static String formatImpl(UInt val);
	static String formatImpl(Long val);
	static String formatImpl(ULong val);
	static String formatImpl(Float val);
	static String formatImpl(Double val);
	static String formatImpl(LDouble val);
	static String formatImpl(Char val);
	static String formatImpl(UChar val);
	static String formatImpl(WChar val);
	static String formatImpl(Char16 val);
	static String formatImpl(Char32 val);
	static String formatImpl(Char* val) { return val; }
	static String formatImpl(const Char* val) { return val; }
	static String formatImpl(WChar* val);
	static String formatImpl(const WChar* val);
	static String formatImpl(const String& val) { return val; }
	static String formatImpl(const Any& val);
	static String formatImpl(const DateTime& val);

	template <typename T>
	static void convertImpl(T& val, const Char* str) { val = std::strtoll(str, nullptr, 0); }
	static void convertImpl(Short& val, const Char* str) { val = (Short)std::strtol(str, nullptr, 0); }
	static void convertImpl(UShort& val, const Char* str) { val = (UShort)std::strtol(str, nullptr, 0); }
	static void convertImpl(Int& val, const Char* str) { val = std::strtol(str, nullptr, 0); }
	static void convertImpl(UInt& val, const Char* str) { val = std::strtoul(str, nullptr, 0); }
	static void convertImpl(Long& val, const Char* str) { val = std::strtoll(str, nullptr, 0); }
	static void convertImpl(ULong& val, const Char* str) { val = std::strtoull(str, nullptr, 0); }
	static void convertImpl(Float& val, const Char* str) { val = std::strtof(str, nullptr); }
	static void convertImpl(Double& val, const Char* str) { val = std::strtod(str, nullptr); }
	static void convertImpl(LDouble& val, const Char* str) { val = std::strtold(str, nullptr); }
	static Long convertLong(const Char* str, std::size_t fPos /*= 0*/, std::size_t lPos /*= npos*/);
};

}
#endif // GEMINI_StringUtil_INCLUDE