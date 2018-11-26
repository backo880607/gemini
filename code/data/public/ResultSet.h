#ifndef GEMINI_SQL_ResultSet_INCLUDE
#define GEMINI_SQL_ResultSet_INCLUDE
#include "Row.h"

namespace gemini {
namespace sql {

class Statement;
class ResultSetImpl;
class GEMINI_SQL_API ResultSet {
  typedef std::shared_ptr<ResultSetImpl> impl_type;
 public:
  typedef RowIterator iterator;
  typedef const iterator const_iterator;

 public:
  ResultSet(impl_type impl);
  ~ResultSet();

  Boolean valid() const { return _impl != nullptr; }

  Long rowCount() const;
  Int columnCount() const;

  String columnName(Int pos) const;

  iterator begin();
  iterator end();

  Boolean moveFirst();
  Boolean moveNext();
  Boolean movePrevious();
  Boolean moveLast();

 private:
  impl_type _impl;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_ResultSet_INCLUDE