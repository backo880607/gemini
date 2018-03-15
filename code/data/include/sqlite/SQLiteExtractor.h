#pragma once
#include "../Extractor.h"

extern "C"
{
	typedef struct sqlite3_stmt sqlite3_stmt;
}

namespace gemini {
namespace data {

class SQLiteExtractor : Extractor
{
public:
	SQLiteExtractor(sqlite3_stmt* pStmt);
	virtual ~SQLiteExtractor();

	virtual Boolean extract(Int pos, Char& val) override;

private:
	sqlite3_stmt* _pStmt;
};
}
}