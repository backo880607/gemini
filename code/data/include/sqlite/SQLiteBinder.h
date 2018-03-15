#pragma once
#include "../Binder.h"

extern "C"
{
	typedef struct sqlite3_stmt sqlite3_stmt;
}

namespace gemini {
namespace data {

class SQLiteBinder : public Binder
{
public:
	SQLiteBinder(sqlite3_stmt* pStmt);
	~SQLiteBinder();

	virtual void bind(Int pos, const Char& val, Direction dir = Direction::PD_IN) override;

private:
	void checkReturn(Int rc);

private:
	sqlite3_stmt* _pStmt;
};

}
}