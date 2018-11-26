#include "../../include/sqlserver/SQLServer.h"
#include "../../include/sqlserver/SQLServerStatement.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace sql {

SQLServer::SQLServer() {}

SQLServer::~SQLServer() {}

std::shared_ptr<StatementImpl> SQLServer::createStatement() {
  return std::shared_ptr<StatementImpl>(new SQLServerStatement(*this));
}

String SQLServer::systemDatabase() const { return "master"; }

String SQLServer::databaseExisted(const String &databaseName) const {
  return StringUtil::SPrintf("SELECT * FROM master.dbo.sysdatabases WHERE name = '%s'", databaseName);
}

String SQLServer::createDatabase(const String &databaseName) const {
  return StringUtil::SPrintf("CREATE DATABASE %s", databaseName);
}

Access::Access() {}

Access::~Access() {}

SQLExcel::SQLExcel() {}

SQLExcel::~SQLExcel() {}

}  // namespace sql
}  // namespace gemini