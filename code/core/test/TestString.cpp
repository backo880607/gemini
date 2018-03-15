#include <boost/test/unit_test.hpp>
#include "DateTime.h"
#include "tools/StringUtil.h"
#include "InitApplication.h"
BOOST_FIXTURE_TEST_SUITE(s_test_aps, InitApplication)

BOOST_AUTO_TEST_CASE(t_test_string_format)
{
	using namespace gemini;
	Boolean bValue = true;
	String str = StringUtil::format(bValue);
	const Boolean cbValue = true;
	str = StringUtil::format(cbValue);
	const Boolean& cbrValue = true;
	str = StringUtil::format(cbrValue);

	Int nValue = 10000;
	str = StringUtil::format(nValue);
	const Int cnValue = nValue;
	str = StringUtil::format(cnValue);
	const Int& cnrValue = nValue;
	str = StringUtil::format(cnrValue);

	UInt unValue = 10;
	str = StringUtil::format(unValue);
	const UInt cunValue = unValue;
	str = StringUtil::format(cunValue);
	const UInt& cunrValue = unValue;
	str = StringUtil::format(cunrValue);

	Float fValue = 10.2f;
	str = StringUtil::format(fValue);
	const Float cfValue = 10.2f;
	str = StringUtil::format(cfValue);
	const Float& cfrValue = 10.3f;
	str = StringUtil::format(cfrValue);

	Double dValue = 10.2;
	str = StringUtil::format(dValue);
	const Double cdValue = 10.2;
	str = StringUtil::format(cdValue);
	const Double& cdrValue = 10.3;
	str = StringUtil::format(cdrValue);

	LDouble ldValue = 10.2;
	str = StringUtil::format(ldValue);
	const LDouble cldValue = 10.2;
	str = StringUtil::format(cldValue);
	const LDouble& cldrValue = ldValue;
	str = StringUtil::format(cldrValue);

	char* cValue = "hello";
	str = StringUtil::format(cValue);
	const WChar* wValue = L"World";
	str = StringUtil::format(wValue);

	String strValue = "Test";
	str = StringUtil::format(strValue);
	String& strrValue = strValue;
	str = StringUtil::format(strrValue);
	const String& cstrrValue = strValue;
	str = StringUtil::format(cstrrValue);

	DateTime dt = DateTime::local();
	str = StringUtil::format(dt);
}

BOOST_AUTO_TEST_CASE(t_test_string_convert)
{
	using namespace gemini;
	String str = "10";
	Int nValue = StringUtil::convert<Int>(str.c_str());
	const Int cnValue = StringUtil::convert<const Int>(str.c_str());
}

BOOST_AUTO_TEST_CASE(t_test_string_join)
{
	using namespace gemini;
	std::vector<int> vecValue = { 1, 2, 3 };
	String str = StringUtil::join(vecValue, ",");
}

BOOST_AUTO_TEST_CASE(t_test_string_parse)
{
	using namespace gemini;
}

BOOST_AUTO_TEST_SUITE_END()