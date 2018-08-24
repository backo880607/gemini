#include "../../include/odbc/ODBCResultSet.h"
#include "../../include/odbc/ODBCRow.h"

namespace gemini {
namespace sql {

ODBCResultSet::ODBCResultSet(SQLHSTMT hstmt) : _hstmt(hstmt) {}

ODBCResultSet::~ODBCResultSet() {}

std::shared_ptr<RowImpl> ODBCResultSet::createRow() const {
  return std::shared_ptr<RowImpl>(new ODBCRow(_hstmt));
}

Boolean ODBCResultSet::next() { return true; }

}  // namespace sql
}  // namespace gemini