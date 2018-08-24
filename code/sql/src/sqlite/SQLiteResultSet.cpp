#include "../../include/sqlite/SQLiteResultSet.h"
#include "../../include/sqlite/SQLiteRow.h"

namespace gemini {
namespace sql {

SQLiteResultSet::SQLiteResultSet(sqlite3_stmt* stmt) : _stmt(stmt) {}

SQLiteResultSet::~SQLiteResultSet() {}

std::shared_ptr<RowImpl> SQLiteResultSet::createRow() const {
  return std::shared_ptr<RowImpl>(new SQLiteRow(_stmt));
}

Boolean SQLiteResultSet::next() { return true; }

}  // namespace sql
}  // namespace gemini