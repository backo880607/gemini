#include "../include/ResultSetImpl.h"
#include "../public/Row.h"
#include "../include/RowImpl.h"

namespace gemini {
namespace sql {

Row::Row(impl_type impl) : _impl(impl) {}

Row::~Row() {}

Boolean Row::isNull(Int col) { return _impl->isNull(col); }

Boolean Row::isNull(const String &name) { return _impl->isNull(name); }

String Row::getText(Int col) { return _impl->getText(col); }

String Row::getText(const String &name) { return _impl->getText(name); }

Any Row::getValue(Int col) { return _impl->getValue(col); }

Any Row::getValue(const String &name) { return _impl->getValue(name); }

RowIterator::RowIterator(const RowIterator &rhs)
    : _pResultSet(rhs._pResultSet) {}

RowIterator::~RowIterator() {}

RowIterator &RowIterator::operator++() {
  if (!_pResultSet->next()) {
    _pResultSet = nullptr;
  }
  return *this;
}

Boolean RowIterator::operator==(const RowIterator &rhs) {
  return _pResultSet == rhs._pResultSet;
}

Boolean RowIterator::operator!=(const RowIterator &rhs) {
  return !(*this == rhs);
}

Row RowIterator::operator*() { return _pResultSet->createRow(); }

void RowIterator::swap(RowIterator &other) {}

}  // namespace sql
}  // namespace gemini