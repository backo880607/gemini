#include "../../include/poco/PocoSQLServer.h"

#include <Poco/Data/ODBC/Connector.h>

namespace gemini {
namespace sql {

PocoSQLServer::PocoSQLServer() {
  Poco::Data::ODBC::Connector::registerConnector();
}

PocoSQLServer::~PocoSQLServer() {
  Poco::Data::ODBC::Connector::unregisterConnector();
}

String PocoSQLServer::connector() const {
  return Poco::Data::ODBC::Connector::KEY;
}

String PocoSQLServer::connectionString() const {
  String str = "host=";
  StringUtil::append(str, getConfig().ip);
  StringUtil::append(str, L";user=", getConfig().username);
  StringUtil::append(str, L";password=", getConfig().password);
  StringUtil::append(str, L";db=", getConfig().database);
  StringUtil::append(
      str,
      L";compress=true;auto-reconnect=true;secure-auth=true;local-infile=true");

  return str;
}

}  // namespace sql
}  // namespace gemini