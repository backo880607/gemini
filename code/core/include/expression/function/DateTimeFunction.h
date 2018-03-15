#pragma once
#include "../../../public/Any.h"

namespace gemini {

class DateTimeFunction
{
public:
	static Any funDate(const std::vector<Any>& params);
	static Any funDateValue(const std::vector<Any>& params);
	static Any funTime(const std::vector<Any>& params);
	static Any funTimeValue(const std::vector<Any>& params);
	static Any funToday(const std::vector<Any>& params);
	static Any funYear(const std::vector<Any>& params);
	static Any funMonth(const std::vector<Any>& params);
	static Any funDay(const std::vector<Any>& params);
	static Any funHour(const std::vector<Any>& params);
	static Any funMinute(const std::vector<Any>& params);
	static Any funSecond(const std::vector<Any>& params);
	static Any funNow(const std::vector<Any>& params);
	static Any funWeekDay(const std::vector<Any>& params);
	static Any funWeekNum(const std::vector<Any>& params);
	static Any funDays(const std::vector<Any>& params);
};

}