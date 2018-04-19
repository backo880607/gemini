#pragma once
#include "../../../public/Any.h"

namespace gemini {

class EntityFunction
{
public:
	static Any funIsType(const std::vector<Any>& params);
	static Any funAsType(const std::vector<Any>& params);
};

}