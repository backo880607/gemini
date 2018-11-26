#include "../../include/oracle/OracleStatement.h"
#include "../../include/oracle/Oracle.h"

namespace gemini {
namespace sql {

OracleStatement::OracleStatement(Oracle &conn) : AdoStatement(conn) {}

OracleStatement::~OracleStatement() {}

String OracleStatement::tableExisted(const String &tblName) const {
  String sql;
  return sql;
}

}  // namespace sql
}  // namespace gemini