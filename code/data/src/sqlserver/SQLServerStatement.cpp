#include "../../include/sqlserver/SQLServer.h"
#include "../../include/sqlserver/SQLServerStatement.h"

namespace gemini {
namespace sql {

SQLServerStatement::SQLServerStatement(SQLServer& conn) : PocoStatement(conn) {}

SQLServerStatement::~SQLServerStatement() {}

String SQLServerStatement::getColumnType(Types type) {
  switch (type) {
    case Types::DOUBLE:
      return "FLOAT";
  }
  return StatementImpl::getColumnType(type);
}

String SQLServerStatement::tableExisted(const String& tblName) const {
  String sql = "SELECT * FROM sysobjects WHERE id = object_id('";
  StringUtil::append(sql, tblName, "')");
  return sql;
}

}  // namespace sql
}  // namespace gemini