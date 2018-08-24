#ifndef GEMINI_USER_SQLServerStatement_INCLUDE
#define GEMINI_USER_SQLServerStatement_INCLUDE
#include "../odbc/ODBCStatement.h"

namespace gemini {
namespace sql {

class SQLServerStatement : public ODBCStatement {
 public:
  SQLServerStatement(ConnectionImpl &conn);
  ~SQLServerStatement();

  virtual String getColumnType(Types type) override;

  virtual void prepareExisted(const String& tblName) override;
};

}  // namespace user
}  // namespace gemini
#endif  // GEMINI_USER_SQLServerStatement_INCLUDE