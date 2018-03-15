#pragma once
#include "../StatementImpl.h"

extern "C"
{
	typedef struct sqlite3 sqlite3;
	typedef struct sqlite3_stmt sqlite3_stmt;
}

namespace gemini {
namespace data {

class SQLiteStatement : public StatementImpl
{
public:
	SQLiteStatement(ConnectionImpl& conn, sqlite3* pDB);
	~SQLiteStatement();

protected:
	virtual Boolean canCompile() const override { return _canCompile; }
	virtual void compileImpl() override;

private:
	sqlite3*		_pDB;
	sqlite3_stmt*	_pStmt;
	Boolean			_canCompile;
};

}
}