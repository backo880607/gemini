#ifndef GEMINI_SQL_SQLiteStatement_INCLUDE
#define GEMINI_SQL_SQLiteStatement_INCLUDE
#include "../StatementImpl.h"

extern "C"
{
	typedef struct sqlite3 sqlite3;
	typedef struct sqlite3_stmt sqlite3_stmt;
};

namespace gemini
{
namespace sql
{

class SQLiteStatement : public StatementImpl
{
  public:
	SQLiteStatement(ConnectionImpl &conn, sqlite3 *pDB);
	~SQLiteStatement();

  protected:
	virtual Boolean canCompile() const override { return _canCompile; }
	virtual void compileImpl() override;

  private:
	sqlite3 *_pDB;
	sqlite3_stmt *_pStmt;
	Boolean _canCompile;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_SQLiteStatement_INCLUDE