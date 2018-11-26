#include "../../include/ado/AdoSQLServer.h"

namespace gemini {
namespace sql {

AdoSQLServer::AdoSQLServer() {}

AdoSQLServer::~AdoSQLServer() {}

String AdoSQLServer::connectionString() const {
  String strConn = "Provider=";
  StringUtil::append(strConn, "SQLOLEDB", ";");
  StringUtil::append(strConn, "Data Source=", getConfig().ip, ",",
                     getConfig().port, ";");
  StringUtil::append(strConn, "User ID=", getConfig().username, ";");
  StringUtil::append(strConn, "Password=", getConfig().password, ";");
  StringUtil::append(strConn, "Initial Catalog=", getConfig().database, ";");
  return strConn;
}

}  // namespace sql
}  // namespace gemini