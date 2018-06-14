#ifndef GEMINI_SQL_Binder_INCLUDE
#define GEMINI_SQL_Binder_INCLUDE
#include "../public/SQLExport.h"

namespace gemini
{
namespace sql
{

class Binder
{
  public:
	/// Binding direction for a parameter.
	enum class Direction
	{
		PD_IN,
		PD_OUT,
		PD_IN_OUT
	};

	Binder();
	virtual ~Binder();

	virtual void bind(Int pos, const Char &val, Direction dir = Direction::PD_IN) = 0;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_Binder_INCLUDE
