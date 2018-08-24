#include "../../include/odbc/ODBCRow.h"

namespace gemini {
namespace sql {

ODBCRow::ODBCRow(SQLHSTMT hstmt) : _hstmt(hstmt) {}

ODBCRow::~ODBCRow() {}

}  // namespace sql
}  // namespace gemini