#include "tools/DoubleUtil.h"

#include <math.h>

namespace gemini {

static Double g_precision = 0.000001;
void DoubleUtil::setPrecision(Double precision) {
	g_precision = precision;
}

Boolean DoubleUtil::isZero(Double value) {
	return (value > -g_precision) && (value < g_precision);
}

Boolean DoubleUtil::isZero(Double value, Double precision) {
	return (value > -precision) && (value < precision);
}

Boolean DoubleUtil::equal(Double lhs, Double rhs) {
	return DoubleUtil::isZero(lhs - rhs);
}

Boolean DoubleUtil::equal(Double lhs, Double rhs, Double precision) {
	return DoubleUtil::isZero(lhs - rhs, precision);
}

Boolean DoubleUtil::less(Double lhs, Double rhs) {
	return (rhs - lhs) > g_precision;
}

Boolean DoubleUtil::less(Double lhs, Double rhs, Double precision) {
	return (rhs - lhs) > precision;
}

Double DoubleUtil::split(Double & fraction, Int index) {
	return Double();
}

Double DoubleUtil::ceil(Double value, Int index) {
	return std::ceil(value);
}

Double DoubleUtil::floor(Double value, Int index) {
	return Double();
}

Double DoubleUtil::round(Double value, Int index) {
	return Double();
}

}