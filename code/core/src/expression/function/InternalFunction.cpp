#include "expression/function/InternalFunction.h"
#include "tools/StringUtil.h"
#include "DateTime.h"

namespace gemini {

Any InternalFunction::add(const std::vector<Any>& params)
{
	return params[0] + params[1];
}

Any InternalFunction::sub(const std::vector<Any>& params)
{
	return params[0] - params[1];
}

Any InternalFunction::multiply(const std::vector<Any>& params)
{
	return params[0] * params[1];
}

Any InternalFunction::division(const std::vector<Any>& params)
{
	return params[0] / params[1];
}

Any InternalFunction::greater(const std::vector<Any>& params)
{
	return params[0] > params[1];
}

Any InternalFunction::greaterEqual(const std::vector<Any>& params)
{
	return params[0] >= params[1];
}

Any InternalFunction::less(const std::vector<Any>& params)
{
	return params[0] < params[1];
}

Any InternalFunction::lessEqual(const std::vector<Any>& params)
{
	return params[0] <= params[1];
}

Any InternalFunction::equal(const std::vector<Any>& params)
{
	return params[0] == params[1];
}

Any InternalFunction::notEqual(const std::vector<Any>& params)
{
	return params[0] != params[1];
}

Any InternalFunction::and(const std::vector<Any>& params)
{
	return params[0].cast<Boolean>() && params[1].cast<Boolean>();
}

Any InternalFunction::or(const std::vector<Any>& params)
{
	return params[0].cast<Boolean>() || params[1].cast<Boolean>();
}

Any InternalFunction::not(const std::vector<Any>& params)
{
	return !params[0].cast<Boolean>();
}

Any InternalFunction::funToStr(const std::vector<Any>& params)
{
	if (params.size() == 1) {
		return StringUtil::format(params[0]);
	}

	if (params.size() == 2) {

	}

	return nullptr;
}

Any InternalFunction::funToInt(const std::vector<Any>& params)
{

}

Any InternalFunction::funToDouble(const std::vector<Any>& params)
{

}

Any InternalFunction::funInclude(const std::vector<Any>& params)
{

}

Any InternalFunction::funIsInt(const std::vector<Any>& params)
{
	return params[0].isType<Int>();
}

Any InternalFunction::funIsDouble(const std::vector<Any>& params)
{
	return params[0].isType<Double>();
}

Any InternalFunction::funIsDigit(const std::vector<Any>& params)
{
	return params[0].isType<Int>() || params[0].isType<Double>();
}

Any InternalFunction::funIsDateTime(const std::vector<Any>& params)
{
	return params[0].isType<DateTime>();
}

Any InternalFunction::funIsBool(const std::vector<Any>& params)
{
	return params[0].isType<Boolean>();
}

Any InternalFunction::funIsStr(const std::vector<Any>& params)
{
	return params[0].isType<String>();
}

Any InternalFunction::funIsEmpty(const std::vector<Any>& params)
{
	if (params.size() != 1) {
		return nullptr;
	}

	if (!params[0]) {
		return true;
	}

	if (params[0].isType<String>()) {
		return params[0].cast<String>().empty();
	}

	if (params[0].isType<DateTime>()) {
		return !params[0].cast<DateTime>().valid();
	}

	return false;
}

Any InternalFunction::funMax(const std::vector<Any>& params)
{

}

Any InternalFunction::funMin(const std::vector<Any>& params)
{

}

Any InternalFunction::funCount(const std::vector<Any>& params)
{

}

Any InternalFunction::funAverage(const std::vector<Any>& params)
{

}

Any InternalFunction::funSum(const std::vector<Any>& params)
{

}

Any InternalFunction::funGuard(const std::vector<Any>& params)
{
	return !params[0] ? params[1] : params[0];
}

}