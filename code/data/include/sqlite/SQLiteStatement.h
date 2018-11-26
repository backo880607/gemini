#ifndef GEMINI_SQL_SQLiteStatement_INCLUDE
#define GEMINI_SQL_SQLiteStatement_INCLUDE
#include "../StatementImpl.h"

extern "C" {
typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;
};

namespace gemini {
namespace sql {

class SQLiteStatement : public StatementImpl {
 public:
  SQLiteStatement(ConnectionImpl &conn, sqlite3 *pDB);
  ~SQLiteStatement();

  virtual void reset() override;

  virtual StatementImpl &operator<<(const Char *value) override {
    _ostr << value;
    return *this;
  }
  virtual String toString() const override { return _ostr.str(); }

  virtual std::shared_ptr<ResultSetImpl> execute(Long &affectRows) override;

  virtual String tableExisted(const String &tblName) const override;
  virtual Int maxInsert() const override { return 10000; }

 protected:
  virtual Binder *createBinder() override;

 private:
  std::ostringstream _ostr;
  sqlite3 *_pDB;
  sqlite3_stmt *_pStmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_SQLiteStatement_INCLUDE