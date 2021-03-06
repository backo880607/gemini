#pragma once
#include "../../../public/Any.h"

namespace gemini {

class LogicFunction
{
public:
	static Any funTrue(const std::vector<Any>& params);
	static Any funFalse(const std::vector<Any>& params);
	static Any funIf(const std::vector<Any>& params);
	static Any funNot(const std::vector<Any>& params);
	static Any funOr(const std::vector<Any>& params);
	static Any funXor(const std::vector<Any>& params);

};

}