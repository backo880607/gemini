#include "../public/ResultSet.h"
#include "../public/Statement.h"
#include "../include/StatementImpl.h"

namespace gemini {
namespace sql {

ResultSet::ResultSet(Statement *stmt)
    : _impl(stmt->_impl->createResultSet()) {}

ResultSet::~ResultSet() {}

Int ResultSet::rowCount() const { return 0; }

Int ResultSet::columnCount() const { return 0; }

ResultSet::const_iterator ResultSet::begin() const {
  return RowIterator(_impl.get());
}

ResultSet::iterator ResultSet::begin() { return RowIterator(_impl.get()); }

ResultSet::const_iterator ResultSet::end() const {
  return RowIterator(nullptr);
}

ResultSet::iterator ResultSet::end() { return RowIterator(nullptr); }

Boolean ResultSet::moveFirst() { return Boolean(); }

Boolean ResultSet::moveNext() { return Boolean(); }

Boolean ResultSet::movePrevious() { return Boolean(); }

Boolean ResultSet::moveLast() { return Boolean(); }

}  // namespace sql
}  // namespace gemini