#include "../../include/ado/Ado.h"
#include "../../public/SQLException.h"
#include "tools/StringUtil.h"
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#include <Windows.h>
#endif

namespace gemini {
namespace sql {

Ado::Ado() { ::CoInitialize(nullptr); }

Ado::~Ado() { ::CoUninitialize(); }

void Ado::open() {
  HRESULT hr;

  try {
    hr = _conn.CreateInstance(__uuidof(ADODB::Connection));
    if (FAILED(hr)) {
    }

    _conn->PutCursorLocation(ADODB::CursorLocationEnum::adUseClient);
    if (getConfig().connectionTimeout > 0) {
      _conn->PutConnectionTimeout(getConfig().connectionTimeout);
	}
    hr = _conn->Open(connectionString().c_str(), "", "", NULL);
    if (FAILED(hr)) {
      return;
    }
  } catch (_com_error e) {
    THROW(ConnectionException, AdoError::format(e));
  }
}

void Ado::onClose() {
  if (_conn != nullptr) {
    try {
      _conn->Close();
    } catch (_com_error& e) {
      THROW(ConnectionException, AdoError::format(e));
    }
    _conn = nullptr;
  }
}

Boolean Ado::isConnected() {
  if (_conn == nullptr) {
    return false;
  }
  try {
    return (_conn->GetState() & ADODB::adStateOpen) != 0;
  } catch (_com_error& e) {
    THROW(ConnectionException, AdoError::format(e));
  }
}

Boolean Ado::getAutoCommit() { return true; }

void Ado::setAutoCommit(Boolean autoCommit) {}

void Ado::begin() {
  try {
    _conn->BeginTrans();
  } catch (_com_error& e) {
    THROW(ConnectionException, AdoError::format(e));
  }
}

void Ado::commit() {
  try {
    _conn->CommitTrans();
  } catch (_com_error& e) {
    THROW(ConnectionException, AdoError::format(e));
  }
}

void Ado::rollback() {
  try {
    _conn->RollbackTrans();
  } catch (_com_error& e) {
    THROW(ConnectionException, AdoError::format(e));
  }
}

Int Ado::getTransactionIsolation() {
  try {
    return _conn->GetIsolationLevel();
  } catch (_com_error& e) {
    THROW(ConnectionException, AdoError::format(e));
  }
}

void Ado::setTransactionIsolation(Int level) {
  try {
    _conn->PutIsolationLevel((ADODB::IsolationLevelEnum)level);
  } catch (_com_error& e) {
    THROW(ConnectionException, AdoError::format(e));
  }
}

Boolean Ado::hasTransactionIsolation(Int level) {
  return 0 != (level & getTransactionIsolation());
}

Boolean Ado::isTransactionIsolation(Int level) {
  return level == getTransactionIsolation();
}
}  // namespace sql
}  // namespace gemini