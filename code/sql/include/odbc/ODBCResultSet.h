#ifndef GEMINI_SQL_ODBCResultSet_INCLUDE
#define GEMINI_SQL_ODBCResultSet_INCLUDE
#include "../ResultSetImpl.h"
#include "Handle.h"

namespace gemini {
namespace sql {

class ODBCStatement;
class ODBCResultSet : public ResultSetImpl {
 public:
  ODBCResultSet(SQLHSTMT hstmt);
  ~ODBCResultSet();

  virtual Boolean valid() const override { return true; }

  virtual std::shared_ptr<RowImpl> createRow() const override;
  virtual Boolean next() override;

 private:
  SQLHSTMT _hstmt;  ///< Ö´ÐÐÓï¾ä¾ä±ú
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_ODBCResultSet_INCLUDE