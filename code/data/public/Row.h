#ifndef GEMINI_SQL_Row_INCLUDE
#define GEMINI_SQL_Row_INCLUDE
#include "Any.h"
#include "SQLExport.h"

namespace gemini {
namespace sql {

class RowImpl;
class GEMINI_SQL_API Row {
  typedef std::shared_ptr<RowImpl> impl_type;

 public:
  Row(impl_type impl);
  ~Row();

  Boolean valid() const { return _impl != nullptr; }

  Boolean isNull(Int col);
  Boolean isNull(const String &name);

  String getText(Int col);
  String getText(const String &name);
  Any getValue(Int col);
  Any getValue(const String &name);
  template <typename T>
  T get(Int col) {
    return getValue(col).cast<T>();
  }
  template <typename T>
  T get(const String &name) {
    return getValue(name).cast<T>();
  }

 private:
  impl_type _impl;
};

class ResultSetImpl;
class GEMINI_SQL_API RowIterator
    : public std::iterator<std::input_iterator_tag, Row> {
 public:
  static const std::size_t POSITION_END;

  RowIterator(ResultSetImpl *pResultSet) : _pResultSet(pResultSet) {}
  RowIterator(const RowIterator &rhs);
  ~RowIterator();

  Boolean valid() const { return _pResultSet != nullptr; }

  RowIterator &operator++();
  Boolean operator==(const RowIterator &rhs);
  Boolean operator!=(const RowIterator &rhs);
  Row operator*();

  void swap(RowIterator &other);

 private:
  ResultSetImpl *_pResultSet;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Row_INCLUDE