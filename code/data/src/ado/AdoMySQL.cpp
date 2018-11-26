#include "../../include/ado/AdoMySQL.h"

namespace gemini {
namespace sql {

AdoMySQL::AdoMySQL() {}

AdoMySQL::~AdoMySQL() {}

String AdoMySQL::connectionString() const {
  String strConn = "DSN=";
  StringUtil::append(strConn, "MySQLODBC", ";");
  StringUtil::append(strConn, "SERVER=", getConfig().ip, ";");
  StringUtil::append(strConn, "PORT", getConfig().port, ";");
  StringUtil::append(strConn, "UID=", getConfig().username, ";");
  StringUtil::append(strConn, "PWD=", getConfig().password, ";");
  StringUtil::append(strConn, "DATABASE=", getConfig().database, ";");
  return strConn;
}

}  // namespace sql
}  // namespace gemini