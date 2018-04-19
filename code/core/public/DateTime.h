#ifndef GEMINI_DateTime_INCLUDE
#define GEMINI_DateTime_INCLUDE
#include "Any.h"

namespace gemini {

/**
 * @brief 日期处理类
 *  精确到秒，内部存储到1970年1月1日零点的时间差
 * 
 */
class Duration;
class CORE_API DateTime : public AnyAbstract {
public:
	DateTime(Long tm = 0) : _time(tm) {};
    DateTime(Int year, Int month, Int day, Int hour = 0, Int minute = 0, Int second = 0);
    DateTime& operator= (Long tm) { _time = tm; return *this; }
	~DateTime() {}

    /**
     * @brief 返回当前的时间。
     * 
     * @return DateTime 
     */
    static DateTime local();

    /**
     * @brief 判断日期类型是否有效
     * 
     * @return 有效性说明 
     *        -<em>false</em> 无效
     *        -<em>true</em>  有效
     */
    Boolean valid() const;
    /**
     * @brief 
     * 
     * @return Long 
     */
    Long getValue() const { return _time; }
    /**
     * @brief 将时间设置成指定的年月日时分秒
     * 
     * @param year 
     * @param month 
     * @param day 
     * @param hour 
     * @param minute 
     * @param second 
     */
    void reset(Int year, Int month, Int day, Int hour = 0, Int minute = 0, Int second = 0);

    /**
     * @brief 获得日期所在的年份
     * 
     * @return Int getYear 
     */
    Int getYear() const;
    /**
     * @brief 获取日期所在的月
     * 
     * @return Int getMonth 
     */
    Int getMonth() const;
    /**
     * @brief 获取日期所在的天
     * 
     * @return Int getDay 
     */
    Int getDay() const;
    /**
     * @brief 获取日期所在小时
     * 
     * @return Int getHour 
     */
    Int getHour() const;
    /**
     * @brief 获取日期所在的分钟
     * 
     * @return Int getMinute 
     */
    Int getMinute() const;
    /**
     * @brief 获取日期所在的秒
     * 
     * @return Int getSecond 
     */
    Int getSecond() const;
    Int getDayOfYear() const;
    Int getDayOfMonth() const;
    Int getDayOfWeek() const;
    Int getWeekOfYear() const;
    Int getWeekOfMonth() const;
    Int getFirstDayOfWeek() const;

    Boolean elapsed(Long tm);

    /**
     * @brief 将日期增加指定的秒数
     * 
     * @param seconds 正数则时间增加seconds秒，负数则时间减少seconds秒
     * @return DateTime& 
     */
	DateTime& addSeconds(Int seconds) { _time += seconds; return *this; }
    /**
     * @brief 将日期增加指定的分钟数
     * 
     * @param minutes 正数则时间增加minutes分，负数则时间减少minutes分
     * @return DateTime& 
     */
	DateTime& addMinutes(Int minutes) { return addSeconds(minutes * 60); }
    /**
     * @brief 将日期增加指定的小时数
     * 
     * @param hours 正数则时间增加hours小时，负数则时间减少hours小时
     * @return DateTime& 
     */
	DateTime& addHours(Int hours) { return addSeconds(hours * 60 * 60); }
    /**
     * @brief 将日期增加指定的天数
     * 
     * @param days 正数则时间增加days天，负数则时间减少days天
     * @return DateTime& 
     */
	DateTime& addDays(Int days) { return addSeconds(days * 24 * 60 * 60); }
    /**
     * @brief 将日期增加指定的月数
     * 
     * @param months 正数则时间增加months月，负数则时间减少months月
     * @return DateTime& 
     */
    DateTime& addMonths(Int months);
    /**
     * @brief 将日期增加指定的年数
     * 
     * @param years 正数则时间增加years年，负数则时间减少years年
     * @return DateTime& 
     */
	DateTime& addYears(Int years) { return addMonths(years * 12); }

    DateTime operator+ (const DateTime& dt) const { return _time + dt._time; }
	DateTime operator+ (const Duration& dur) const;
    DateTime operator- (const DateTime& dt) const { return _time - dt._time; }
	DateTime operator- (const Duration& dur) const;
    DateTime& operator+= (const DateTime& dt) { _time += dt._time; return *this; }
	DateTime& operator+= (const Duration& dur);
    DateTime& operator-= (const DateTime& dt) { _time -= dt._time; return *this; }
	DateTime& operator-= (const Duration& dur);

    Boolean operator== (const DateTime& dt) const { return _time == dt._time; }
	Boolean operator!= (const DateTime& dt) const { return !(*this == dt); }
	Boolean operator> (const DateTime& dt) const { return _time > dt._time; }
	Boolean operator>= (const DateTime& dt) const { return !(*this < dt); }
	Boolean operator< (const DateTime& dt) const { return dt > *this ; }
	Boolean operator<= (const DateTime& dt) const { return !(*this > dt); }
	
	// any support
	virtual Any operator+ (const Any& rhs) const;
	virtual void operator+= (const Any& rhs);
	virtual Any operator- (const Any& rhs) const;
	virtual void operator-= (const Any& rhs);
	virtual Any operator* (const Any& rhs) const;
	virtual void operator*= (const Any& rhs);
	virtual Any operator/ (const Any& rhs) const;
	virtual void operator/= (const Any& rhs);
    virtual Boolean operator== (const Any& rhs) const;
	virtual Boolean operator< (const Any& rhs) const;

	virtual String str() const;
	String str(const Char* f) const;
	static DateTime valueOf(const Char* str);
private:
	friend class StringUtil;
    Long _time;
};

class CORE_API Duration : public AnyAbstract {
public:
	Duration(Int value = 0) : _value(value) {}
	~Duration() {}

	Duration operator+ (const Duration& dur) const { return _value + dur._value; }
	DateTime operator+ (const DateTime& dt) const { return dt.getValue() + _value; }
	Duration operator- (const Duration& dur) const { return _value - dur._value; }
	Duration& operator+= (const Duration& dur) { _value += dur._value; return *this; }
	Duration& operator-= (const Duration& dur) { _value -= dur._value; return *this; }

	Boolean operator== (const Duration& dur) const { return _value == dur._value; }
	Boolean operator!= (const Duration& dur) const { return !(*this == dur); }
	Boolean operator> (const Duration& dur) const { return _value > dur._value; }
	Boolean operator>= (const Duration& dur) const { return !(*this < dur); }
	Boolean operator< (const Duration& dur) const { return dur > *this; }
	Boolean operator<= (const Duration& dur) const { return !(*this > dur); }

	// any support
	virtual Any operator+ (const Any& rhs) const;
	virtual void operator+= (const Any& rhs);
	virtual Any operator- (const Any& rhs) const;
	virtual void operator-= (const Any& rhs);
	virtual Any operator* (const Any& rhs) const;
	virtual void operator*= (const Any& rhs);
	virtual Any operator/ (const Any& rhs) const;
	virtual void operator/= (const Any& rhs);
	virtual Boolean operator== (const Any& rhs) const;
	virtual Boolean operator< (const Any& rhs) const;

	virtual String str() const;
	static Duration valueOf(const Char* str);
private:
	friend class DateTime;
	Int _value;
};

}
#endif // GEMINI_DateTime_INCLUDE