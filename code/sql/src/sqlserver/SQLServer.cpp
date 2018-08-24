#include "../../include/sqlserver/SQLServer.h"
#include "../../../core/public/tools/StringUtil.h"
#include "../../include/sqlserver/SQLServerStatement.h"

namespace gemini {
namespace sql {

SQLServer::SQLServer() {}

SQLServer::~SQLServer() {}

std::shared_ptr<StatementImpl> SQLServer::createStatement() {
  return std::shared_ptr<StatementImpl>(new SQLServerStatement(*this));
}

String SQLServer::connectionString() const {
  String connectionStr = "DRIVER=";
  connectionStr.append("SQL Server Native Client 11.0").append(";");
  connectionStr.append("Trusted_Connection=no;");
  connectionStr.append("UID=").append(getConfig().username).append(";");
  connectionStr.append("PWD=").append(getConfig().password).append(";");
  connectionStr.append("DATABASE=").append(getConfig().database).append(";");
  connectionStr.append("SERVER=").append(getConfig().ip).append(";");
  connectionStr.append("PORT=")
      .append(StringUtil::format(getConfig().port))
      .append(";");
  return connectionStr;
}

Access::Access() {}

Access::~Access() {}

SQLExcel::SQLExcel() {}

SQLExcel::~SQLExcel() {}

}  // namespace sql
}  // namespace gemini