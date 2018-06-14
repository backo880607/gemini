#include "../../include/sqlite/SQLiteStatement.h"
#include "sqlite3.h"

namespace gemini
{
namespace sql
{

SQLiteStatement::SQLiteStatement(ConnectionImpl &conn, sqlite3 *pDB)
	: StatementImpl(conn), _pDB(pDB), _canCompile(true)
{
}

SQLiteStatement::~SQLiteStatement()
{
}

void SQLiteStatement::compileImpl()
{
	String statement(toString());

	sqlite3_stmt *pStmt = 0;
	const Char *pSql = statement.c_str();

	Int rc = SQLITE_OK;
	const Char *pLeftover = 0;
	Boolean queryFound = false;

	do
	{
		rc = sqlite3_prepare_v2(_pDB, pSql, -1, &pStmt, &pLeftover);
		if (rc != SQLITE_OK)
		{
			if (pStmt)
				sqlite3_finalize(pStmt);
			pStmt = 0;
			String errMsg = sqlite3_errmsg(_pDB);
		}
		else if (rc == SQLITE_OK && pStmt)
		{
			queryFound = true;
		}
		else if (rc == SQLITE_OK && !pStmt) // comment/whitespace ignore
		{
			pSql = pLeftover;
			if (std::strlen(pSql) == 0)
			{
				// empty statement or an conditional statement! like CREATE IF NOT EXISTS
				// this is valid
				queryFound = true;
			}
		}
	} while (rc == SQLITE_OK && !pStmt && !queryFound);
}

} // namespace sql
} // namespace gemini