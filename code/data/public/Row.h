#pragma once
#include "DataExport.h"
#include "Any.h"

namespace gemini {
namespace data {

class GEMINI_DATA_API Row
{
public:
	Row();
	~Row();

	Any getValue(Int col);
	Any getValue(const String& name);
	template <typename T>
	T get(Int col) {
		return getValue(col).cast<T>();
	}
	template <typename T>
	T get(const String& name) {
		return getValue(name).cast<T>();
	}


};

}
}