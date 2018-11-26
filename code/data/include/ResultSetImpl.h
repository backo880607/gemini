#ifndef GEMINI_SQL_ResultSetImpl_INCLUDE
#define GEMINI_SQL_ResultSetImpl_INCLUDE
#include "../public/SQLExport.h"

namespace gemini {
namespace sql {

class RowImpl;
class StatementImpl;
class ResultSetImpl {
 public:
  ResultSetImpl();
  virtual ~ResultSetImpl();

  virtual Long rowCount() const = 0;
  virtual Int columnCount() const = 0;

  virtual String columnName(Int pos) const = 0;

  virtual std::shared_ptr<RowImpl> createRow() const = 0;
  virtual Boolean next() = 0;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_ResultSetImpl_INCLUDE