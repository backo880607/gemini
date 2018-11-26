#include "../../include/sqlite/SQLiteRow.h"
#include "sqlite3.h"

namespace gemini {
namespace sql {

SQLiteRow::SQLiteRow(sqlite3_stmt* stmt) : _stmt(stmt) {}

SQLiteRow::~SQLiteRow() {}

Boolean SQLiteRow::isNull(Int col) {
  return sqlite3_column_value(_stmt, col) == nullptr;
}

Boolean SQLiteRow::isNull(const String& name) { return false; }

String SQLiteRow::getText(Int col) { return (const Char*)sqlite3_column_text(_stmt, col); }

String SQLiteRow::getText(const String& name) { return ""; }

Any SQLiteRow::getValue(Int col) { return nullptr; }

Any SQLiteRow::getValue(const String& name) { return nullptr; }

}  // namespace sql
}  // namespace gemini