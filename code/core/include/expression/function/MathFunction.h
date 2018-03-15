#pragma once
#include "../../../public/Any.h"

namespace gemini {

class MathFunction
{
public:
	static Any funAbs(const std::vector<Any>& params);
	static Any funSin(const std::vector<Any>& params);
	static Any funSinh(const std::vector<Any>& params);
	static Any funCos(const std::vector<Any>& params);
	static Any funTan(const std::vector<Any>& params);
	static Any funTanh(const std::vector<Any>& params);
	static Any funASin(const std::vector<Any>& params);
	static Any funACos(const std::vector<Any>& params);
	static Any funATan(const std::vector<Any>& params);
	static Any funToDegrees(const std::vector<Any>& params);
	static Any funToRadians(const std::vector<Any>& params);
	static Any funExp(const std::vector<Any>& params);
	static Any funLog(const std::vector<Any>& params);
	static Any funLog10(const std::vector<Any>& params);
	static Any funLog1p(const std::vector<Any>& params);
	static Any funFloor(const std::vector<Any>& params);
	static Any funCeil(const std::vector<Any>& params);
	static Any funRound(const std::vector<Any>& params);
	static Any funSqrt(const std::vector<Any>& params);
	static Any funCbrt(const std::vector<Any>& params);
	static Any funPow(const std::vector<Any>& params);
	static Any funSignum(const std::vector<Any>& params);
	static Any funRandom(const std::vector<Any>& params);
};

}