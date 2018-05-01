#pragma once
#include "../../../public/Any.h"

namespace gemini {

class InternalFunction
{
public:
	static Any add(const std::vector<Any>& params);
	static Any sub(const std::vector<Any>& params);
	static Any multiply(const std::vector<Any>& params);
	static Any division(const std::vector<Any>& params);
	static Any greater(const std::vector<Any>& params);
	static Any greaterEqual(const std::vector<Any>& params);
	static Any less(const std::vector<Any>& params);
	static Any lessEqual(const std::vector<Any>& params);
	static Any equal(const std::vector<Any>& params);
	static Any notEqual(const std::vector<Any>& params);
	static Any funAnd(const std::vector<Any>& params);
	static Any funOr(const std::vector<Any>& params);
	static Any funNot(const std::vector<Any>& params);
	static Any funToStr(const std::vector<Any>& params);
	static Any funToInt(const std::vector<Any>& params);
	static Any funToDouble(const std::vector<Any>& params);
	static Any funInclude(const std::vector<Any>& params);
	static Any funIsInt(const std::vector<Any>& params);
	static Any funIsDouble(const std::vector<Any>& params);
	static Any funIsDigit(const std::vector<Any>& params);
	static Any funIsDateTime(const std::vector<Any>& params);
	static Any funIsBool(const std::vector<Any>& params);
	static Any funIsStr(const std::vector<Any>& params);
	static Any funIsEmpty(const std::vector<Any>& params);
	static Any funMax(const std::vector<Any>& params);
	static Any funMin(const std::vector<Any>& params);
	static Any funCount(const std::vector<Any>& params);
	static Any funAverage(const std::vector<Any>& params);
	static Any funSum(const std::vector<Any>& params);
	static Any funGuard(const std::vector<Any>& params);
};

}