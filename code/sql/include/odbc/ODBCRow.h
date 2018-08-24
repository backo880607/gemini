#ifndef GEMINI_SQL_ODBCRow_INCLUDE
#define GEMINI_SQL_ODBCRow_INCLUDE
#include "../RowImpl.h"
#include "Error.h"

namespace gemini {
namespace sql {

class ODBCRow : public RowImpl {
 public:
  ODBCRow(SQLHSTMT hstmt);
  ~ODBCRow();

 private:
  SQLHSTMT _hstmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_ODBCRow_INCLUDE