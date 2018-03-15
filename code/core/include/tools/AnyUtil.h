#pragma once

#include "..\Any.h"

namespace gemini {

class CORE_API AnyUtil final {
public:
	template <typename T>
	static T cast(const Any& value) {

	}
	template <typename T>
	static const T& refCast(const Any& value) {

	}
	template <typename T>
	static T& refCast(Any& value) {

	}

	static Any add(const Any& lhs, const Any& rhs);
	static Any sub(const Any& lhs, const Any& rhs);
	static Any multiply(const Any& lhs, const Any& rhs);
	static Any division(const Any& lhs, const Any& rhs);

	/*static Any division(const Any& lhs, const Any& rhs);
	static Any division(const Any& lhs, const Any& rhs);
	static Any division(const Any& lhs, const Any& rhs);
	static Any division(const Any& lhs, const Any& rhs);
	static Any division(const Any& lhs, const Any& rhs);
	static Any division(const Any& lhs, const Any& rhs);*/
};

}