#include "../../include/sqlite/SQLiteBinder.h"
#include "sqlite3.h"

namespace gemini {
namespace data {

SQLiteBinder::SQLiteBinder(sqlite3_stmt* pStmt)
	: _pStmt(pStmt)
{
}

SQLiteBinder::~SQLiteBinder()
{

}

void SQLiteBinder::bind(Int pos, const Char & val, Direction dir)
{
	checkReturn(sqlite3_bind_int(_pStmt, pos, (Int)val));
}

void SQLiteBinder::checkReturn(Int rc)
{

}

}
}