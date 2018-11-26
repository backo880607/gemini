#include "../../../core/public/tools/StringUtil.h"
#include "../../include/oracle/Oracle.h"
#include "../../include/oracle/OracleStatement.h"

#include <Poco/Data/ODBC/Connector.h>

#include <objbase.h>

namespace gemini {
namespace sql {

Oracle::Oracle() {
  CoInitialize(nullptr);
  Poco::Data::ODBC::Connector::registerConnector();
}

Oracle::~Oracle() { Poco::Data::ODBC::Connector::unregisterConnector(); }

std::shared_ptr<StatementImpl> Oracle::createStatement() {
  return std::shared_ptr<StatementImpl>(new OracleStatement(*this));
}

String Oracle::systemDatabase() const { return "information_schema"; }

String Oracle::databaseExisted(const String &databaseName) const { return ""; }

String Oracle::createDatabase(const String &databaseName) const {
  return StringUtil::SPrintf("CREATE DATABASE %s", databaseName);
}

}  // namespace sql
}  // namespace gemini