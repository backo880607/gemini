#ifndef GEMINI_SQL_SQLiteResultSet_INCLUDE
#define GEMINI_SQL_SQLiteResultSet_INCLUDE
#include "../ResultSetImpl.h"

extern "C" {
typedef struct sqlite3_stmt sqlite3_stmt;
};

namespace gemini {
namespace sql {

class SQLiteStatement;
class SQLiteResultSet : public ResultSetImpl {
 public:
  SQLiteResultSet(sqlite3_stmt* stmt);
  ~SQLiteResultSet();

  virtual Long rowCount() const override;
  virtual Int columnCount() const override;

  virtual String columnName(Int pos) const override;

  virtual std::shared_ptr<RowImpl> createRow() const override;
  virtual Boolean next() override;

 private:
  sqlite3_stmt* _stmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLiteResultSet_INCLUDE