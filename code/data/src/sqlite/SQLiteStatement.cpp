#include "../../include/sqlite/SQLiteResultSet.h"
#include "../../include/sqlite/SQLiteStatement.h"
#include "../../include/sqlite/SQLiteBinder.h"
#include "sqlite3.h"

namespace gemini {
namespace sql {

SQLiteStatement::SQLiteStatement(ConnectionImpl &conn, sqlite3 *pDB)
    : StatementImpl(conn), _pDB(pDB) {}

SQLiteStatement::~SQLiteStatement() {}

void SQLiteStatement::reset() { sqlite3_reset(_pStmt); }

std::shared_ptr<ResultSetImpl> SQLiteStatement::execute(Long &affectRows) {
  String statement(toString());

  _pStmt = 0;
  const Char *pSql = statement.c_str();

  Int rc = SQLITE_OK;
  const Char *pLeftover = 0;
  Boolean queryFound = false;

  do {
    rc = sqlite3_prepare_v2(_pDB, pSql, -1, &_pStmt, &pLeftover);
    if (rc != SQLITE_OK) {
      String errMsg = sqlite3_errmsg(_pDB);
      if (_pStmt != nullptr) sqlite3_finalize(_pStmt);
      _pStmt = nullptr;
    } else if (rc == SQLITE_OK && _pStmt) {
      queryFound = true;
    } else if (rc == SQLITE_OK && !_pStmt) {
      pSql = pLeftover;
      if (std::strlen(pSql) == 0) {
        // empty statement or an conditional statement! like CREATE IF NOT
        // EXISTS this is valid
        queryFound = true;
      }
    }
  } while (rc == SQLITE_OK && !_pStmt && !queryFound);

  rc = sqlite3_step(_pStmt);
  if (SQLITE_OK != rc && SQLITE_DONE != rc) {
    String errMsg = sqlite3_errmsg(_pDB);
    if (_pStmt != nullptr) sqlite3_finalize(_pStmt);
    _pStmt = nullptr;
    return nullptr;
  }

  return std::shared_ptr<ResultSetImpl>(new SQLiteResultSet(_pStmt));
}

String SQLiteStatement::tableExisted(const String &tblName) const {
  return StringUtil::SPrintf("SELECT * FROM sqlite_master WHERE type='table' AND name='%s'", tblName);
}

Binder *SQLiteStatement::createBinder() { return new SQLiteBinder(_pStmt); }

}  // namespace sql
}  // namespace gemini