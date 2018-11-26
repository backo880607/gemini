#include "../../include/mysql/MySQL.h"
#include "../../include/mysql/MySQLStatement.h"

namespace gemini {
namespace sql {

MySQLStatement::MySQLStatement(MySQL &conn) : AdoStatement(conn) {}

MySQLStatement::~MySQLStatement() {}

String MySQLStatement::getColumnType(Types type) {
  switch (type) {
    case Types::BOOLEAN:
      return "TINYINT";
  }
  return StatementImpl::getColumnType(type);
}

String MySQLStatement::tableExisted(const String &tblName) const {
  String sql =
      "select * from information_schema.TABLES t where t.TABLE_SCHEMA "
      "='";
  StringUtil::append(sql, getConfig().database, "' and t.TABLE_NAME ='",
                     tblName, "'");
  return sql;
}

}  // namespace sql
}  // namespace gemini