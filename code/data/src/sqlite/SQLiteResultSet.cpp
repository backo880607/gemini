#include "../../include/sqlite/SQLiteResultSet.h"
#include "../../include/sqlite/SQLiteRow.h"
#include "sqlite3.h"

namespace gemini {
namespace sql {

SQLiteResultSet::SQLiteResultSet(sqlite3_stmt* stmt) : _stmt(stmt) {}

SQLiteResultSet::~SQLiteResultSet() {}

Long SQLiteResultSet::rowCount() const { return 0; }

Int SQLiteResultSet::columnCount() const { return sqlite3_column_count(_stmt); }

String SQLiteResultSet::columnName(Int pos) const {
  return sqlite3_column_name(_stmt, pos);
}

std::shared_ptr<RowImpl> SQLiteResultSet::createRow() const {
  return std::shared_ptr<RowImpl>(new SQLiteRow(_stmt));
}

Boolean SQLiteResultSet::next() { return true; }

}  // namespace sql
}  // namespace gemini