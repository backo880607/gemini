#include "../public/DateTime.h"

#include <time.h>

namespace gemini {

DateTime::DateTime(Int year, Int month, Int day, Int hour, Int minute, Int second)
{
	reset(year, month, day, hour, minute, second);
}

DateTime DateTime::local()
{
	return time(nullptr);
}

Boolean DateTime::valid() const
{
	return _time > 0 && _time < 32223372036;
}

void DateTime::reset(Int year, Int month, Int day, Int hour, Int minute, Int second)
{
	tm t1;
	t1.tm_year = year - 1900;
	t1.tm_mon = month - 1;
	t1.tm_mday = day;
	t1.tm_hour = hour;
	t1.tm_min = minute;
	t1.tm_sec = second;

	_time = mktime(&t1);
}

Int DateTime::getYear() const
{
	tm* t1 = localtime(&_time);
	return t1->tm_year + 1900;
}

Int DateTime::getMonth() const
{
	tm* t1 = localtime(&_time);
	return t1->tm_mon + 1;
}

Int DateTime::getDay() const
{
	tm* t1 = localtime(&_time);
	return t1->tm_mday;
}

Int DateTime::getHour() const
{
	tm* t1 = localtime(&_time);
	return t1->tm_hour;
}

Int DateTime::getMinute() const
{
	tm* t1 = localtime(&_time);
	return t1->tm_min;
}

Int DateTime::getSecond() const
{
	tm* t1 = localtime(&_time);
	return t1->tm_sec;
}

Int DateTime::getDayOfYear() const
{
	tm* t1 = localtime(&_time);
	char temp[128];
	strftime(temp, 128, "%j", t1);
	return atoi(temp);
}

Int DateTime::getDayOfMonth() const
{
	tm* t1 = localtime(&_time);
	return t1->tm_mday;
}

Int DateTime::getDayOfWeek() const
{
	tm* t1 = localtime(&_time);
	return t1->tm_wday == 0 ? 7 : t1->tm_wday;
}

Int DateTime::getWeekOfYear() const
{
	tm* t1 = localtime(&_time);
	char temp[128];
	strftime(temp, 128, "%W", t1);
	return atoi(temp) + 1;
}

Int DateTime::getWeekOfMonth() const
{
	tm* t1 = localtime(&_time);
	char temp[128];
	strftime(temp, 128, "%w", t1);
	return atoi(temp);
}

Int DateTime::getFirstDayOfWeek() const
{
	DateTime dt(_time);
	Int dayDiff = getDayOfWeek() - 1;
	dt.addDays(-dayDiff);
	return dt.getDay();
}

Boolean DateTime::elapsed(Long tm)
{
	DateTime dtNow = DateTime::local();
	return (dtNow._time - _time) >= tm;
}

DateTime & DateTime::addMonths(Int months)
{
	tm* t1 = localtime(&_time);

	Int absMonth = months;
	if (absMonth < 0)
		absMonth = abs(absMonth);

	Int year = absMonth / 12;
	Int mon = absMonth % 12;
	if (months > 0)
	{
		*this = DateTime(getYear() + year, getMonth() + mon, t1->tm_mday, t1->tm_hour, t1->tm_min, t1->tm_sec);
	}
	else
	{
		*this = DateTime(getYear() - year, getMonth() - mon, t1->tm_mday, t1->tm_hour, t1->tm_min, t1->tm_sec);
	}

	return *this;
}

Any DateTime::operator+ (const Any& rhs) const
{
	if (rhs.isType<DateTime>()) {
		return *this + rhs.cast<DateTime>();
	}
	return nullptr;
}

void DateTime::operator+= (const Any& rhs)
{
	if (rhs.isType<DateTime>()) {
		*this += rhs.cast<DateTime>();
	}
}

Any DateTime::operator- (const Any& rhs) const
{
	if (rhs.isType<DateTime>()) {
		return *this - rhs.cast<DateTime>();
	}
	return nullptr;
}

void DateTime::operator-= (const Any& rhs)
{
	if (rhs.isType<DateTime>()) {
		*this += rhs.cast<DateTime>();
	}
}

Any DateTime::operator* (const Any& rhs) const
{
	return nullptr;
}

void DateTime::operator*= (const Any& rhs)
{
}

Any DateTime::operator/ (const Any& rhs) const
{
	return nullptr;
}

void DateTime::operator/= (const Any& rhs)
{
}

Boolean DateTime::operator== (const Any& rhs) const
{
	if (rhs.isType<DateTime>()) {
		return *this == rhs.cast<DateTime>();
	}
	return false;
}

Boolean DateTime::operator< (const Any& rhs) const
{
	if (rhs.isType<DateTime>()) {
		return *this < rhs.cast<DateTime>();
	}
	return false;
}

}