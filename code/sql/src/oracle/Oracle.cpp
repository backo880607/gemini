#include "../../include/oracle/Oracle.h"
#include "../../../core/public/tools/StringUtil.h"

namespace gemini {
namespace sql {

Oracle::Oracle() {}

Oracle::~Oracle() {}

String Oracle::connectionString() const {
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

}  // namespace sql
}  // namespace gemini