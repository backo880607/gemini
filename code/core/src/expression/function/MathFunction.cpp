#include "expression/function/MathFunction.h"

#include <stdlib.h>
#include <math.h>

namespace gemini {

Any MathFunction::funAbs(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return abs(param1.cast<Long>());
	}
	return nullptr;
}

Any MathFunction::funSin(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return sin(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return sin(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funSinh(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return sinh(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return sinh(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funCos(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return cos(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return cos(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funTan(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return tan(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return tan(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funTanh(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return tanh(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return tanh(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funASin(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return asin(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return asin(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funACos(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return acos(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return acos(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funATan(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return atan(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return atan(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funToDegrees(const std::vector<Any>& params)
{

}

Any MathFunction::funToRadians(const std::vector<Any>& params)
{

}

Any MathFunction::funExp(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return exp(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return exp(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funLog(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return log(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return log(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funLog10(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return log10(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return log10(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funLog1p(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return log1p(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return log1p(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funFloor(const std::vector<Any>& params)
{
	Double digits = 0;
	if (params.size() == 2) {
		const Any& param2 = params[1];
		if (param2.isType<Long>()) {
			digits = (Double)param2.cast<Long>();
		} else if (param2.isType<Double>()) {
			digits = param2.cast<Double>();
		}
	}
	digits = pow(10.0, digits);
	Double value = 0.0;
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		value = (Double)param1.cast<Long>();
	} else if (param1.isType<Double>()) {
		value = param1.cast<Double>();
	}

	value = floor(value*digits) / digits;
	return params.size() == 1 ? (Long)value : value;
}

Any MathFunction::funCeil(const std::vector<Any>& params)
{
	Double digits = 0;
	if (params.size() == 2) {
		const Any& param2 = params[1];
		if (param2.isType<Long>()) {
			digits = (Double)param2.cast<Long>();
		} else if (param2.isType<Double>()) {
			digits = param2.cast<Double>();
		}
	}
	digits = pow(10.0, digits);
	Double value = 0.0;
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		value = (Double)param1.cast<Long>();
	} else if (param1.isType<Double>()) {
		value = param1.cast<Double>();
	}

	value = ceil(value*digits) / digits;
	return params.size() == 1 ? (Long)value : value;
}

Any MathFunction::funRound(const std::vector<Any>& params)
{
	Double digits = 0;
	if (params.size() == 2) {
		const Any& param2 = params[1];
		if (param2.isType<Long>()) {
			digits = (Double)param2.cast<Long>();
		} else if (param2.isType<Double>()) {
			digits = param2.cast<Double>();
		}
	}
	digits = pow(10.0, digits);
	Double value = 0.0;
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		value = (Double)param1.cast<Long>();
	} else if (param1.isType<Double>()) {
		value = param1.cast<Double>();
	}

	value = round(value*digits) / digits;
	return params.size() == 1 ? (Long)value : value;
}

Any MathFunction::funSqrt(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return sqrt(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return sqrt(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funCbrt(const std::vector<Any>& params)
{
	const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return cbrt(param1.cast<Long>());
	} else if (param1.isType<Double>()) {
		return cbrt(param1.cast<Double>());
	}
	return nullptr;
}

Any MathFunction::funPow(const std::vector<Any>& params)
{
	Double value1 = params[0].isType<Long>() ? params[0].cast<Long>() : params[0].cast<Double>();
	Double value2 = params[1].isType<Long>() ? params[1].cast<Long>() : params[1].cast<Double>();
	return pow(value1, value2);
}

Any MathFunction::funSignum(const std::vector<Any>& params)
{
	/*const Any& param1 = params[0];
	if (param1.isType<Long>()) {
		return signum(param1.cast<Long>());
	}
	else if (param1.isType<Double>()) {
		return signum(param1.cast<Double>());
	}*/
	return nullptr;
}

Any MathFunction::funRandom(const std::vector<Any>& params)
{
	return rand();
}

}