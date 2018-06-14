#include "../../include/sqlite/SQLiteExtractor.h"
#include "sqlite3.h"

namespace gemini
{
namespace sql
{

SQLiteExtractor::SQLiteExtractor(sqlite3_stmt *pStmt)
	: _pStmt(pStmt)
{
}

SQLiteExtractor::~SQLiteExtractor()
{
}

Boolean SQLiteExtractor::extract(Int pos, Char &val)
{
	if (isNull(pos))
		return false;
	val = sqlite3_column_int(_pStmt, (int)pos);
	return true;
}

} // namespace sql
} // namespace gemini