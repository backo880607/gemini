#include "../../include/ado/Ado.h"
#include "../../include/ado/AdoBinder.h"
#include "../../include/ado/AdoResultSet.h"
#include "../../include/ado/AdoStatement.h"

namespace gemini {
namespace sql {

AdoStatement::AdoStatement(Ado &conn) : StatementImpl(conn) {
  _stmt.CreateInstance(__uuidof(ADODB::Command));
  _stmt->ActiveConnection = conn._conn;
}

AdoStatement::~AdoStatement() {}

void AdoStatement::reset() {
  _ostr.clear();
  _ostr.str("");
}

std::shared_ptr<ResultSetImpl> AdoStatement::execute(Long &affectRows) {
  ADODB::_RecordsetPtr recordSet;
  _stmt->PutCommandText(_ostr.str().c_str());
  _variant_t vRecordAffected;
  try {
    recordSet = _stmt->Execute(&vRecordAffected, nullptr, ADODB::adCmdText);
    if (recordSet == nullptr || recordSet->GetState() == ADODB::adStateClosed) {
      return nullptr;
    }
  } catch (_com_error &e) {
    THROW(ExecutionException, AdoError::format(e));
  }

  recordSet->put_CursorType(ADODB::CursorTypeEnum::adOpenStatic);
  affectRows = recordSet->GetRecordCount();
  return std::shared_ptr<ResultSetImpl>(new AdoResultSet(recordSet));
}

Binder *AdoStatement::createBinder() { return new AdoBinder(_stmt); }

}  // namespace sql
}  // namespace gemini