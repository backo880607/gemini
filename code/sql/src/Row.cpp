#include "../include/ResultSetImpl.h"
#include "../public/Row.h"

namespace gemini {
namespace sql {

Row::Row(impl_type impl) : _impl(impl) {}

Row::~Row() {}

Int Row::columnCount() { return 0; }

Boolean Row::isNull(Int col) { return true; }

Boolean Row::isNull(const String &name) { return true; }

Any Row::getValue(Int col) { return nullptr; }

Any Row::getValue(const String &name) { return nullptr; }

RowIterator::RowIterator(ResultSetImpl *pResultSet) : _pResultSet(pResultSet) {}

RowIterator::RowIterator(const RowIterator &rhs) {}

RowIterator::~RowIterator() {}

RowIterator &RowIterator::operator++() {
  if (!_pResultSet->next()) {
    _pResultSet = nullptr;
  }
  return *this;
}

Boolean RowIterator::operator==(const RowIterator &rhs) {
  if (rhs._pResultSet == nullptr) {
    return _pResultSet == nullptr;
  }
  return false;
}

Boolean RowIterator::operator!=(const RowIterator &rhs) {
  return !(*this == rhs);
}

Row RowIterator::operator*() { return _pResultSet->createRow(); }

void RowIterator::swap(RowIterator &other) {}

}  // namespace sql
}  // namespace gemini