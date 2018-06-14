#ifndef GEMINI_SQL_RowIterator_INCLUDE
#define GEMINI_SQL_RowIterator_INCLUDE
#include "SQLExport.h"

namespace gemini
{
namespace sql
{

class ResultSet;
class GEMINI_SQL_API RowIterator
{
public:
	static const std::size_t POSITION_END;

	RowIterator(const ResultSet *pResultSet, Boolean positionEnd);
	~RowIterator();

	void swap(RowIterator &other);

private:
	const ResultSet *_pResultSet;
	mutable Int _position;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_RowIterator_INCLUDE