#include "../../include/odbc/ODBC.h"
#include "../../include/odbc/ODBCResultSet.h"
#include "../../include/odbc/ODBCStatement.h"

namespace gemini {
namespace sql {

ODBCStatement::ODBCStatement(ConnectionImpl &conn)
    : StatementImpl(conn),
      _canCompile(true),
      _hdbc(((ODBC *)&conn)->_hdbc),
      _hstmt(nullptr) {
  if (ErrorUtil::isError(SQLAllocHandle(SQL_HANDLE_STMT, _hdbc, &_hstmt))) {
    _hstmt = nullptr;
    return;
  }
  Int queryTimeout = conn.getConfig().readTimeout;
  if (queryTimeout >= 0) {
    SQLULEN uqt = static_cast<SQLULEN>(queryTimeout);
    SQLSetStmtAttr(_hstmt, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)uqt, 0);
  }

  _binder = std::shared_ptr<ODBCBinder>(new ODBCBinder(_hstmt, nullptr));
}

ODBCStatement::~ODBCStatement() {
  try {
    SQLFreeHandle(SQL_HANDLE_STMT, _hstmt);
  } catch (...) {
  }
}

std::shared_ptr<ResultSetImpl> ODBCStatement::createResultSet() const {
  return std::shared_ptr<ResultSetImpl>(new ODBCResultSet(_hstmt));
}

void ODBCStatement::execute() {
  ErrorUtil::checkError(_hstmt, SQLExecute(_hstmt));
}

Int ODBCStatement::affectedRowCount() { return 0; }

void ODBCStatement::resetImpl() {}

void ODBCStatement::compileImpl() {
  ErrorUtil::checkError(
      _hstmt, SQLPrepare(_hstmt, (SQLCHAR *)toString().c_str(), SQL_NTS));
  _canCompile = false;
}

void ODBCStatement::prepareExisted(const String &tblName) {}

const MetaColumn &ODBCStatement::metaColumn(Int pos) {
  THROW_IF(pos < 0 || pos >= _metaColumns.size(), BoundaryException,
           "Invalid column number: ", pos);
  if (_metaColumns[pos] == nullptr) {
    _metaColumns[pos] = _binder->metaColumn(pos);
  }

  return *_metaColumns[pos];
}

std::shared_ptr<Binder> ODBCStatement::getBinder() { return _binder; }

}  // namespace sql
}  // namespace gemini