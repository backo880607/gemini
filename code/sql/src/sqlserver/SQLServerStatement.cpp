#include "../../include/sqlserver/SQLServerStatement.h"

namespace gemini {
namespace sql {

SQLServerStatement::SQLServerStatement(ConnectionImpl& conn)
    : ODBCStatement(conn) {}

SQLServerStatement::~SQLServerStatement() {}

String SQLServerStatement::getColumnType(Types type) {
  switch (type) {
    case Types::DOUBLE:
      return "FLOAT";
  }
  return ODBCStatement::getColumnType(type);
}

void SQLServerStatement::prepareExisted(const String& tblName) {
  *this << "SELECT COUNT(*) FROM sysobjects WHERE id= object_id('" << tblName
        << "')";
}

}  // namespace sql
}  // namespace gemini