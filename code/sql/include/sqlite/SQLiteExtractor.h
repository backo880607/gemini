#ifndef GEMINI_SQL_SQLiteExtractor_INCLUDE
#define GEMINI_SQL_SQLiteExtractor_INCLUDE
#include "../Extractor.h"

extern "C"
{
	typedef struct sqlite3_stmt sqlite3_stmt;
};

namespace gemini
{
namespace sql
{

class SQLiteExtractor : Extractor
{
  public:
	SQLiteExtractor(sqlite3_stmt *pStmt);
	virtual ~SQLiteExtractor();

	virtual Boolean extract(Int pos, Char &val) override;

  private:
	sqlite3_stmt *_pStmt;
};

} // namespace sql
} // namespace gemini
#endif // !GEMINI_SQL_SQLiteExtractor_INCLUDE