#pragma once
#include "../public/DataExport.h"

namespace gemini {
namespace data {

class Binder
{
public:
	/// Binding direction for a parameter.
	enum class Direction {
		PD_IN,
		PD_OUT,
		PD_IN_OUT
	};

	Binder();
	virtual ~Binder();

	virtual void bind(Int pos, const Char& val, Direction dir = Direction::PD_IN) = 0;
};

}
}
