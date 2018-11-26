#ifndef GEMINI_SQL_MySQLStatement_INCLUDE
#define GEMINI_SQL_MySQLStatement_INCLUDE
//#include "../poco/PocoStatement.h"
#include "../ado/AdoStatement.h"

namespace gemini {
namespace sql {

class MySQL;
class MySQLStatement : public AdoStatement {
 public:
  MySQLStatement(MySQL &conn);
  ~MySQLStatement();

  virtual String getColumnType(Types type) override;

  virtual String tableExisted(const String &tblName) const override;
  virtual Int maxInsert() const override { return 10000; }
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_MySQLStatement_INCLUDE