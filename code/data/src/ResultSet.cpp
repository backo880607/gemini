#include "../include/ResultSetImpl.h"
#include "../include/StatementImpl.h"
#include "../public/ResultSet.h"
#include "../public/Statement.h"

namespace gemini {
namespace sql {

ResultSet::ResultSet(impl_type impl) : _impl(impl) {}

ResultSet::~ResultSet() {}

Long ResultSet::rowCount() const { return (Long)_impl->rowCount(); }

Int ResultSet::columnCount() const { return (Int)_impl->columnCount(); }

String ResultSet::columnName(Int pos) const { return _impl->columnName(pos); }

ResultSet::iterator ResultSet::begin() { return _impl->next() ? &*_impl : nullptr; }

ResultSet::iterator ResultSet::end() { return nullptr; }

Boolean ResultSet::moveFirst() { return false; }

Boolean ResultSet::moveNext() { return false; }

Boolean ResultSet::movePrevious() { return false; }

Boolean ResultSet::moveLast() { return false; }

}  // namespace sql
}  // namespace gemini