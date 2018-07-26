#include "DateTime.h"
#include "message/Exception.h"
#include "session/Subject.h"
#include "tools/LocaleUtil.h"
#include "tools/StringUtil.h"

#include <time.h>

namespace gemini {

DateTime::DateTime(Int year, Int month, Int day, Int hour, Int minute,
                   Int second) {
  reset(year, month, day, hour, minute, second);
}

DateTime DateTime::local() { return time(nullptr); }

Boolean DateTime::valid() const { return _time > 0 && _time < 32223372036; }

void DateTime::reset(Int year, Int month, Int day, Int hour, Int minute,
                     Int second) {
  tm t1;
  t1.tm_year = year - 1900;
  t1.tm_mon = month - 1;
  t1.tm_mday = day;
  t1.tm_hour = hour;
  t1.tm_min = minute;
  t1.tm_sec = second;

  _time = mktime(&t1);
}

Int DateTime::getYear() const {
  tm* t1 = localtime(&_time);
  return t1->tm_year + 1900;
}

Int DateTime::getMonth() const {
  tm* t1 = localtime(&_time);
  return t1->tm_mon + 1;
}

Int DateTime::getDay() const {
  tm* t1 = localtime(&_time);
  return t1->tm_mday;
}

Int DateTime::getHour() const {
  tm* t1 = localtime(&_time);
  return t1->tm_hour;
}

Int DateTime::getMinute() const {
  tm* t1 = localtime(&_time);
  return t1->tm_min;
}

Int DateTime::getSecond() const {
  tm* t1 = localtime(&_time);
  return t1->tm_sec;
}

Int DateTime::getDayOfYear() const {
  tm* t1 = localtime(&_time);
  char temp[128];
  strftime(temp, 128, "%j", t1);
  return atoi(temp);
}

Int DateTime::getDayOfMonth() const {
  tm* t1 = localtime(&_time);
  return t1->tm_mday;
}

Int DateTime::getDayOfWeek() const {
  tm* t1 = localtime(&_time);
  return t1->tm_wday == 0 ? 7 : t1->tm_wday;
}

Int DateTime::getWeekOfYear() const {
  tm* t1 = localtime(&_time);
  char temp[128];
  strftime(temp, 128, "%W", t1);
  return atoi(temp) + 1;
}

Int DateTime::getWeekOfMonth() const {
  tm* t1 = localtime(&_time);
  char temp[128];
  strftime(temp, 128, "%w", t1);
  return atoi(temp);
}

Int DateTime::getFirstDayOfWeek() const {
  DateTime dt(_time);
  Int dayDiff = getDayOfWeek() - 1;
  dt.addDays(-dayDiff);
  return dt.getDay();
}

Boolean DateTime::elapsed(Long tm) {
  DateTime dtNow = DateTime::local();
  return (dtNow._time - _time) >= tm;
}

DateTime& DateTime::addMonths(Int months) {
  tm* t1 = localtime(&_time);

  Int absMonth = months;
  if (absMonth < 0) absMonth = abs(absMonth);

  Int year = absMonth / 12;
  Int mon = absMonth % 12;
  if (months > 0) {
    *this = DateTime(getYear() + year, getMonth() + mon, t1->tm_mday,
                     t1->tm_hour, t1->tm_min, t1->tm_sec);
  } else {
    *this = DateTime(getYear() - year, getMonth() - mon, t1->tm_mday,
                     t1->tm_hour, t1->tm_min, t1->tm_sec);
  }

  return *this;
}

DateTime DateTime::operator+(const Duration& dur) const {
  return DateTime(getValue() + dur._value);
}

DateTime DateTime::operator-(const Duration& dur) const {
  return DateTime(getValue() - dur._value);
}

DateTime& DateTime::operator+=(const Duration& dur) {
  _time += dur._value;
  return *this;
}

DateTime& DateTime::operator-=(const Duration& dur) {
  _time -= dur._value;
  return *this;
}

Any DateTime::operator+(const Any& rhs) const {
  if (rhs.isType<DateTime>()) {
    return *this + rhs.cast<DateTime>();
  } else if (rhs.isType<Duration>()) {
    return *this + rhs.cast<Duration>();
  }
  THROW(OperandException);
}

void DateTime::operator+=(const Any& rhs) {
  if (rhs.isType<DateTime>()) {
    *this += rhs.cast<DateTime>();
  } else if (rhs.isType<Duration>()) {
    *this += rhs.cast<Duration>();
  }
  THROW(OperandException);
}

Any DateTime::operator-(const Any& rhs) const {
  if (rhs.isType<DateTime>()) {
    return *this - rhs.cast<DateTime>();
  } else if (rhs.isType<Duration>()) {
    return *this - rhs.cast<Duration>();
  }
  THROW(OperandException);
}

void DateTime::operator-=(const Any& rhs) {
  if (rhs.isType<DateTime>()) {
    *this -= rhs.cast<DateTime>();
  } else if (rhs.isType<Duration>()) {
    *this -= rhs.cast<Duration>();
  }
  THROW(OperandException);
}

Boolean DateTime::operator==(const Any& rhs) const {
  if (rhs.isType<DateTime>()) {
    return *this == rhs.cast<DateTime>();
  }
  THROW(OperandException);
}

Boolean DateTime::operator<(const Any& rhs) const {
  if (rhs.isType<DateTime>()) {
    return *this < rhs.cast<DateTime>();
  }
  THROW(OperandException);
}

std::ostringstream& getDateTimeOSStream() {
  return Subject::get().getSession()->get<LocaleUtil>().getOSS(true);
}
String DateTime::str() const {
  std::ostringstream& ss = getDateTimeOSStream();
  ss << boost::locale::as::datetime << boost::locale::as::local_time
     << getValue();
  return ss.str();
}

String DateTime::str(const Char* f) const {
  tm* t1 = localtime(&_time);
  Char temp[128];
  strftime(temp, 128, f, t1);
  return temp;
}

std::istringstream& getDateTimeISStream(const Char* str) {
  return Subject::get().getSession()->get<LocaleUtil>().getISS(str);
}
DateTime DateTime::valueOf(const Char* str) {
  DateTime dt;
  std::istringstream& ss = getDateTimeISStream(str);
  ss >> boost::locale::as::datetime >> boost::locale::as::local_time >>
      dt._time;
  return dt;
}

Any Duration::operator+(const Any& rhs) const {
  if (rhs.isType<Duration>()) {
    return *this + rhs.cast<Duration>();
  } else if (rhs.isType<DateTime>()) {
    return rhs.cast<DateTime>() + *this;
  }
  THROW(OperandException);
}

void Duration::operator+=(const Any& rhs) {
  if (rhs.isType<Duration>()) {
    *this += rhs.cast<Duration>();
  }
  THROW(OperandException);
}

Any Duration::operator-(const Any& rhs) const {
  if (rhs.isType<Duration>()) {
    return *this - rhs.cast<Duration>();
  }
  THROW(OperandException);
}

void Duration::operator-=(const Any& rhs) {
  if (rhs.isType<Duration>()) {
    *this -= rhs.cast<Duration>();
  }
  THROW(OperandException);
}

Boolean Duration::operator==(const Any& rhs) const {
  if (rhs.isType<Duration>()) {
    return _value == rhs.cast<Duration>()._value;
  }
  THROW(OperandException);
}

Boolean Duration::operator<(const Any& rhs) const {
  if (rhs.isType<Duration>()) {
    return _value < rhs.cast<Duration>()._value;
  }
  THROW(OperandException);
}

String Duration::str() const { return StringUtil::format(_value); }

Duration Duration::valueOf(const Char* str) {
  return StringUtil::convert<Int>(str);
}

void DurationExtend::parse() {

}

}  // namespace gemini