#include "../../include/ado/AdoResultSet.h"
#include "../../include/ado/AdoRow.h"
#include "../../public/SQLException.h"

namespace gemini {
namespace sql {

AdoResultSet::AdoResultSet(ADODB::_RecordsetPtr recordSet)
    : _recordSet(recordSet) {}

AdoResultSet::~AdoResultSet() {}

Long AdoResultSet::rowCount() const {
  try {
    return _recordSet->GetRecordCount();
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
}

Int AdoResultSet::columnCount() const {
  try {
    return _recordSet->GetFields()->GetCount();
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
}

String AdoResultSet::columnName(Int pos) const {
  try {
    return (
        const Char*)(_recordSet->GetFields()->GetItem((long)pos)->GetName());
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
}

std::shared_ptr<RowImpl> AdoResultSet::createRow() const {
  try {
    return std::shared_ptr<RowImpl>(new AdoRow(_recordSet->GetFields()));
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
}

Boolean AdoResultSet::next() {
  if (_recordSet->adoEOF) {
    return false;
  }

  try {
    _recordSet->MoveNext();
  } catch (_com_error e) {
    THROW(ExecutionException, AdoError::format(e));
  }
  return true;
}

}  // namespace sql
}  // namespace gemini