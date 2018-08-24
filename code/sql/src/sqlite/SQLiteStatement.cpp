#include "../../include/sqlite/SQLiteResultSet.h"
#include "../../include/sqlite/SQLiteStatement.h"
#include "sqlite3.h"

namespace gemini {
namespace sql {

SQLiteStatement::SQLiteStatement(ConnectionImpl &conn, sqlite3 *pDB)
    : StatementImpl(conn), _pDB(pDB), _canCompile(true) {}

SQLiteStatement::~SQLiteStatement() { _canCompile = true; }

void SQLiteStatement::resetImpl() {}

std::shared_ptr<ResultSetImpl> SQLiteStatement::createResultSet() const {
  return std::shared_ptr<ResultSetImpl>(new SQLiteResultSet(_pStmt));
}

void SQLiteStatement::compileImpl() {
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

  if (std::strlen(pLeftover) > 0) {
    _canCompile = true;
  } else
    _canCompile = false;
}

void SQLiteStatement::execute() {
  Int rc = SQLITE_OK;
  rc = sqlite3_step(_pStmt);
  if (SQLITE_OK != rc && SQLITE_DONE != rc) {
    String errMsg = sqlite3_errmsg(_pDB);
    if (_pStmt != nullptr) sqlite3_finalize(_pStmt);
    _pStmt = nullptr;
    return;
  }
}

void SQLiteStatement::prepareExisted(const String &tblName) {
  *this << "SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name='"
        << tblName << "'";
}

Int SQLiteStatement::affectedRowCount() { return sqlite3_changes(_pDB); }

const MetaColumn &SQLiteStatement::metaColumn(Int pos) { THROW(DataBaseException) }

}  // namespace sql
}  // namespace gemini