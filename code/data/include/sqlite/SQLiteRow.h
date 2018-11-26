#ifndef GEMINI_SQL_SQLiteRow_INCLUDE
#define GEMINI_SQL_SQLiteRow_INCLUDE
#include "../RowImpl.h"

extern "C" {
typedef struct sqlite3_stmt sqlite3_stmt;
};

namespace gemini {
namespace sql {

class SQLiteRow : public RowImpl {
 public:
  SQLiteRow(sqlite3_stmt* stmt);
  ~SQLiteRow();

  virtual Boolean isNull(Int col) override;
  virtual Boolean isNull(const String &name) override;

  virtual String getText(Int col) override;
  virtual String getText(const String &name) override;
  virtual Any getValue(Int col) override;
  virtual Any getValue(const String &name) override;

 private:
  sqlite3_stmt* _stmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLiteRow_INCLUDE