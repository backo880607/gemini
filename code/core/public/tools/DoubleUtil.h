#ifndef GEMINI_DoubleUtil_INCLUDE
#define GEMINI_DoubleUtil_INCLUDE
#include "../Common.h"

namespace gemini {

class CORE_API DoubleUtil final
{
	DoubleUtil() = delete;
	DoubleUtil(const DoubleUtil&) = delete;
	DoubleUtil& operator=(const DoubleUtil&) = delete;
public:
	static void setPrecision(LDouble precision);

	static Boolean isZero(LDouble value);
	static Boolean isZero(LDouble value, LDouble precision);

	static Boolean equal(LDouble lhs, LDouble rhs);
	static Boolean equal(LDouble lhs, LDouble rhs, LDouble precision);
	static Boolean notEqual(LDouble lhs, LDouble rhs) { return !DoubleUtil::equal(lhs, rhs); }
	static Boolean notEqual(LDouble lhs, LDouble rhs, LDouble precision) { return !DoubleUtil::equal(lhs, rhs, precision); }
	static Boolean less(LDouble lhs, LDouble rhs);
	static Boolean less(LDouble lhs, LDouble rhs, LDouble precision);
	static Boolean lessEqual(LDouble lhs, LDouble rhs) { return !DoubleUtil::less(rhs, lhs); }
	static Boolean lessEqual(LDouble lhs, LDouble rhs, LDouble precision) { return !DoubleUtil::less(rhs, lhs, precision); }
	static Boolean greater(LDouble lhs, LDouble rhs) { return DoubleUtil::less(rhs, lhs); }
	static Boolean greater(LDouble lhs, LDouble rhs, LDouble precision) { return DoubleUtil::less(rhs, lhs, precision); }
	static Boolean greaterEqual(LDouble lhs, LDouble rhs) { return !DoubleUtil::less(lhs, rhs); }
	static Boolean greaterEqual(LDouble lhs, LDouble rhs, LDouble precision) { return !DoubleUtil::less(lhs, rhs, precision); }

	//////////////////////////////////////////////////////////////////////////
	//  以下部分用到的索引表示：小数点为索引0，小数部分索引为负值，整数部分索引为正值

	// 将浮点数分割成两部分，函数返回前部分，fraction返回后部分
	static Double split(Double& fraction, Int index = 0);
	// 舍掉index以后的值，前一位加1
	static Double ceil(Double value, Int index = 0);
	// 舍掉index以后的值
	static Double floor(Double value, Int index = 0);
	// 对index后的值四舍五入
	static Double round(Double value, Int index = 0);
};

}
#endif // GEMINI_DoubleUtil_INCLUDE