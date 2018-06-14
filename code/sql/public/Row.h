#ifndef GEMINI_SQL_Row_INCLUDE
#define GEMINI_SQL_Row_INCLUDE
#include "SQLExport.h"
#include "Any.h"

namespace gemini
{
namespace sql
{

class GEMINI_SQL_API Row
{
  public:
	Row();
	~Row();

	Any getValue(Int col);
	Any getValue(const String &name);
	template <typename T>
	T get(Int col)
	{
		return getValue(col).cast<T>();
	}
	template <typename T>
	T get(const String &name)
	{
		return getValue(name).cast<T>();
	}
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_Row_INCLUDE