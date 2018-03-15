#include <boost/test/unit_test.hpp>

#include "DateTime.h"
#include "tools\StringUtil.h"

#include <boost\system\error_code.hpp>
#include <boost\locale.hpp>

void formatDateTime()
{
	using namespace gemini;
	DateTime dt = DateTime::local();
	String strDt = StringUtil::format(dt);
	strDt = StringUtil::format(dt, u8"%Y-%m-%d %H:%M:%S");

	int num = 0;
}

BOOST_AUTO_TEST_CASE(t_test_datetime)
{
	using namespace gemini;

/*	boost::locale::generator gen;
	std::locale targetLoc = gen("en_US.UTF-8");
	std::locale::global(targetLoc);
	
	//std::cout.imbue(targetLoc);
	std::cout << boost::locale::as::number << 12345 << std::endl;*/
	// 测试最小日期，
	// 因为有时区影响，因此下面获得的年月日时分秒为：
	// 1970-01-01 08:00:00
	DateTime minTime(0);
	Int year = minTime.getYear();
	Int month = minTime.getMonth();
	Int day = minTime.getDay();
	Int hour = minTime.getHour();
	Int minute = minTime.getMinute();
	Int second = minTime.getSecond();
	
	// 测试当前日期
	DateTime dt = DateTime::local();

	// 
	dt.reset(2018, 1, 14, 17, 21);
	year = dt.getYear();
	month = dt.getMonth();
	day = dt.getDay();
	hour = dt.getHour();
	minute = dt.getMinute();
	second = dt.getSecond();
	Long time = dt.getTime();
	
	formatDateTime();
}