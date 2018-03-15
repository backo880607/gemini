#include "../../public/tools/DoubleUtil.h"

#include <math.h>

namespace gemini {

static LDouble g_precision = 0.000001;
void DoubleUtil::setPrecision(LDouble precision)
{
	g_precision = precision;
}

Boolean DoubleUtil::isZero(LDouble value)
{
	return (value > -g_precision) && (value < g_precision);
}

Boolean DoubleUtil::isZero(LDouble value, LDouble precision)
{
	return (value > -precision) && (value < precision);
}

Boolean DoubleUtil::equal(LDouble lhs, LDouble rhs)
{
	return DoubleUtil::isZero(lhs - rhs);
}

Boolean DoubleUtil::equal(LDouble lhs, LDouble rhs, LDouble precision)
{
	return DoubleUtil::isZero(lhs - rhs, precision);
}

Boolean DoubleUtil::less(LDouble lhs, LDouble rhs)
{
	return (rhs - lhs) > g_precision;
}

Boolean DoubleUtil::less(LDouble lhs, LDouble rhs, LDouble precision)
{
	return (rhs - lhs) > precision;
}

Double DoubleUtil::split(Double & fraction, Int index)
{
	return Double();
}

Double DoubleUtil::ceil(Double value, Int index)
{
	return std::ceil(value);
}

Double DoubleUtil::floor(Double value, Int index)
{
	return Double();
}

Double DoubleUtil::round(Double value, Int index)
{
	return Double();
}

}