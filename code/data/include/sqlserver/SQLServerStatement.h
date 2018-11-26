#ifndef GEMINI_USER_SQLServerStatement_INCLUDE
#define GEMINI_USER_SQLServerStatement_INCLUDE
#include "../ado/AdoStatement.h"
#include "../poco/PocoStatement.h"

namespace gemini {
namespace sql {

class SQLServer;
class SQLServerStatement : public PocoStatement {
 public:
  SQLServerStatement(SQLServer& conn);
  ~SQLServerStatement();

  virtual String getColumnType(Types type) override;

  virtual String tableExisted(const String& tblName) const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_USER_SQLServerStatement_INCLUDE