#include "../../include/odbc/ODBCExtractor.h"

namespace gemini {
namespace sql {

ODBCExtractor::ODBCExtractor(SQLHSTMT hstmt) : _hstmt(hstmt) {}

ODBCExtractor::~ODBCExtractor() {}

Boolean ODBCExtractor::extract(Int pos, Boolean &value) {
  return extractImpl(pos, value, SQL_C_BIT);
}

Boolean ODBCExtractor::extract(Int pos, Char &value) {
  return extractImpl(pos, value, SQL_C_TINYINT);
}

Boolean ODBCExtractor::extract(Int pos, Short &value) {
  return extractImpl(pos, value, SQL_C_SHORT);
}

Boolean ODBCExtractor::extract(Int pos, Int &value) {
  return extractImpl(pos, value, SQL_C_LONG);
}

Boolean ODBCExtractor::extract(Int pos, Long &value) {
  return extractImpl(pos, value, SQL_C_SBIGINT);
}

Boolean ODBCExtractor::extract(Int pos, Float &value) {
  return extractImpl(pos, value, SQL_C_FLOAT);
}

Boolean ODBCExtractor::extract(Int pos, Double &value) {
  return extractImpl(pos, value, SQL_C_DOUBLE);
}

Boolean ODBCExtractor::extract(Int pos, String &value) {
  return extractImpl(pos, value, SQL_C_SHORT);
}

Boolean ODBCExtractor::extract(Int pos, DateTime &value) {
  return extractImpl(pos, value, SQL_C_SHORT);
}

Boolean ODBCExtractor::extract(Int pos, Duration &value) {
  return extractImpl(pos, value, SQL_C_SHORT);
}

Boolean ODBCExtractor::extract(Int pos, DurationExtend &value) {
  return extractImpl(pos, value, SQL_C_SHORT);
}

}  // namespace sql
}  // namespace gemini