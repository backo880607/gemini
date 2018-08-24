#include "../../include/sqlite/SQLiteRow.h"

namespace gemini {
namespace sql {

SQLiteRow::SQLiteRow(sqlite3_stmt* stmt) : _stmt(stmt) {}

SQLiteRow::~SQLiteRow() {}

}  // namespace sql
}  // namespace gemini