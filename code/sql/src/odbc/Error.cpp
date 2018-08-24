#include "../../include/odbc/Error.h"
#include "../../public/SQLException.h"
#include "tools/StringUtil.h"

namespace gemini {
namespace sql {

Boolean ErrorUtil::isError(SQLRETURN rc) { return (0 != (rc & (~1))); }

void ErrorUtil::checkError(SQLHDBC hdbc, SQLRETURN rc) {
  if (isError(rc)) {
    THROW(ConnectionException, ConnectionError(hdbc).toString());
  }
}

}  // namespace sql
}  // namespace gemini