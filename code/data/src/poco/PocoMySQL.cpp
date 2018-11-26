#include "../../include/poco/PocoMySQL.h"

#include <Poco/Data/MySql/Connector.h>

namespace gemini {
namespace sql {

PocoMySQL::PocoMySQL() { Poco::Data::MySQL::Connector::registerConnector(); }

PocoMySQL::~PocoMySQL() { Poco::Data::MySQL::Connector::unregisterConnector(); }

String PocoMySQL::connector() const {
  return Poco::Data::MySQL::Connector::KEY;
}

String PocoMySQL::connectionString() const {
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