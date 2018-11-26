#ifndef GEMINI_SQL_OracleStatement_INCLUDE
#define GEMINI_SQL_OracleStatement_INCLUDE
#include "../ado/AdoStatement.h"

namespace gemini {
namespace sql {

class Oracle;
class OracleStatement : public AdoStatement {
 public:
  OracleStatement(Oracle &conn);
  ~OracleStatement();

  virtual String tableExisted(const String &tblName) const;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_OracleStatement_INCLUDE