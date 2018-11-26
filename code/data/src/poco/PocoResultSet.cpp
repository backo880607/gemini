#include "../../include/poco/PocoResultSet.h"
#include "../../include/poco/PocoRow.h"

#include <Poco/Data/RecordSet.h>

namespace gemini {
namespace sql {

PocoResultSet::PocoResultSet(Poco::Data::Statement& stmt)
    : _recordSet(new Poco::Data::RecordSet(stmt)) {}

PocoResultSet::~PocoResultSet() {}

Long PocoResultSet::rowCount() const { return _recordSet->rowCount(); }

Int PocoResultSet::columnCount() const { return _recordSet->columnCount(); }

String PocoResultSet::columnName(Int pos) const { return ""; }

std::shared_ptr<RowImpl> PocoResultSet::createRow() const {
  return std::shared_ptr<RowImpl>(new PocoRow(&_recordSet->row(0)));
}

Boolean PocoResultSet::next() { return false; }

}  // namespace sql
}  // namespace gemini