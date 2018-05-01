#include "expression/function/DateTimeFunction.h"
#include "DateTime.h"
#include "tools/StringUtil.h"

namespace gemini {

Any DateTimeFunction::funDate(const std::vector<Any>& params) {
	Long year = params[0].cast<Long>();
	Long month = params[1].cast<Long>();
	Long day = params[2].cast<Long>();
	return DateTime((Int)year, (Int)month, (Int)day);
}

Any DateTimeFunction::funDateValue(const std::vector<Any>& params) {
	//return StringUtil::convert
}

Any DateTimeFunction::funTime(const std::vector<Any>& params) {
	Long hour = params[0].cast<Long>();
	Long minute = params[1].cast<Long>();
	Long second = params[2].cast<Long>();
	return DateTime(0, 0, 0, (Int)hour, (Int)minute, (Int)second);
}

Any DateTimeFunction::funTimeValue(const std::vector<Any>& params) {

}

Any DateTimeFunction::funToday(const std::vector<Any>& params) {
	DateTime dt = DateTime::local();
	return DateTime(dt.getYear(), dt.getMonth(), dt.getDay());
}

Any DateTimeFunction::funYear(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getYear();
}

Any DateTimeFunction::funMonth(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getMonth();
}

Any DateTimeFunction::funDay(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getDay();
}

Any DateTimeFunction::funHour(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getHour();
}

Any DateTimeFunction::funMinute(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getMinute();
}

Any DateTimeFunction::funSecond(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getSecond();
}

Any DateTimeFunction::funNow(const std::vector<Any>& params) {
	return DateTime::local();
}

Any DateTimeFunction::funWeekDay(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getDayOfWeek();
}

Any DateTimeFunction::funWeekNum(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getWeekOfYear();
}

Any DateTimeFunction::funDays(const std::vector<Any>& params) {
	return params[0].cast<DateTime>().getDayOfYear();
}

}