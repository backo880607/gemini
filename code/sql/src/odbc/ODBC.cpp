#include "../../include/odbc/Error.h"
#include "../../include/odbc/ODBC.h"
#include "../../include/odbc/ODBCStatement.h"
#include "Buffer.h"
#include "tools/StringUtil.h"

#include <sqlext.h>
#include <thread>

namespace gemini {
namespace sql {

ODBC::ODBC() {}

ODBC::~ODBC() {}

Boolean ODBC::open() {
  // 申请环境句柄
  THROW_IF(ErrorUtil::isError(
               SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_henv)),
           DataBaseException)

  // 设置环境属性
  THROW_IF(ErrorUtil::isError(SQLSetEnvAttr(_henv, SQL_ATTR_ODBC_VERSION,
                                            (void*)SQL_OV_ODBC3, 0)),
           DataBaseException)

  // 申请数据库连接句柄
  THROW_IF(ErrorUtil::isError(SQLAllocHandle(SQL_HANDLE_DBC, _henv, &_hdbc)),
           DataBaseException)

  // timeout
  if (getConfig().connectionTimeout > 0) {
    SQLULEN tout = static_cast<SQLULEN>(getConfig().connectionTimeout);
    ErrorUtil::checkError(
        _hdbc,
        SQLSetConnectAttr(_hdbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)tout, 0));
  }

  SQLCHAR connectOutput[512] = {0};
  SQLSMALLINT result;

  // connect
  ErrorUtil::checkError(
      _hdbc,
      SQLDriverConnect(_hdbc, nullptr, (SQLCHAR*)connectionString().c_str(),
                       (SQLSMALLINT)SQL_NTS, connectOutput,
                       sizeof(connectOutput), &result, SQL_DRIVER_NOPROMPT));

  // checkError(SQLSetConnectAttr(_hdbc, SQL_ATTR_QUIET_MODE, 0, 0));
  return true;
}

void ODBC::close() {
  if (!isConnected()) return;

  try {
    commit();
  } catch (ConnectionException&) {
  }

  SQLDisconnect(_hdbc);
}

std::shared_ptr<StatementImpl> ODBC::createStatement() {
  return std::shared_ptr<StatementImpl>(new ODBCStatement(*this));
}

Boolean ODBC::isConnected() {
  SQLULEN value = 0;
  if (!SQLGetConnectAttrImpl(SQL_ATTR_CONNECTION_DEAD, &value, 0, 0))
    return false;
  return (SQL_CD_FALSE == value);
}

Boolean ODBC::getAutoCommit() {
  SQLULEN value = 0;
  SQLGetConnectAttrImpl(SQL_ATTR_AUTOCOMMIT, &value, 0, 0);
  return (0 != value);
}

void ODBC::setAutoCommit(Boolean autoCommit) {
  ErrorUtil::checkError(
      _hdbc, SQLSetConnectAttr(_hdbc, SQL_ATTR_AUTOCOMMIT,
                               autoCommit ? (SQLPOINTER)SQL_AUTOCOMMIT_ON
                                          : (SQLPOINTER)SQL_AUTOCOMMIT_OFF,
                               SQL_IS_UINTEGER));
}

void ODBC::begin() {
  THROW_IF(getAutoCommit(), AccessException, "Session in auto commit mode.");
  {
    std::lock_guard<std::mutex> l(_mutex);
    THROW_IF(_inTransaction, AccessException, "Transaction in progress.");
    _inTransaction = true;
  }
}

void ODBC::commit() {
  if (!getAutoCommit()) {
    THROW_IF(ErrorUtil::isError(SQLEndTran(SQL_HANDLE_DBC, _hdbc, SQL_COMMIT)),
             ConnectionException);
  }

  _inTransaction = false;
}

void ODBC::rollback() {
  if (!getAutoCommit()) {
    THROW_IF(
        ErrorUtil::isError(SQLEndTran(SQL_HANDLE_DBC, _hdbc, SQL_ROLLBACK)),
        ConnectionException);
  }

  _inTransaction = false;
}

Boolean ODBC::canTransact() {
  if (ODBC_TXN_CAPABILITY_UNKNOWN == _canTransact) {
    SQLUSMALLINT ret;
    SQLGetInfoImpl(SQL_TXN_CAPABLE, &ret, 0, 0);
    _canTransact = (SQL_TC_NONE != ret) ? ODBC_TXN_CAPABILITY_TRUE
                                        : ODBC_TXN_CAPABILITY_FALSE;
  }

  return ODBC_TXN_CAPABILITY_TRUE == _canTransact;
}

Boolean ODBC::isTransaction() {
  if (!canTransact()) return false;

  SQLULEN value = 0;
  SQLGetConnectAttrImpl(SQL_ATTR_AUTOCOMMIT, &value, 0, 0);
  return value == 0 ? _inTransaction : false;
}

Int ODBC::getTransactionIsolation() {
  SQLULEN isolation = 0;
  SQLGetConnectAttrImpl(SQL_ATTR_TXN_ISOLATION, &isolation, 0, 0);
  return transactionIsolation(isolation);
}

void ODBC::setTransactionIsolation(Int level) {
  Int isolation = 0;
  if (level & TRANSACTION_READ_UNCOMMITTED)
    isolation |= SQL_TXN_READ_UNCOMMITTED;

  if (level & TRANSACTION_READ_COMMITTED) isolation |= SQL_TXN_READ_COMMITTED;

  if (level & TRANSACTION_REPEATABLE_READ) isolation |= SQL_TXN_REPEATABLE_READ;

  if (level & TRANSACTION_SERIALIZABLE) isolation |= SQL_TXN_SERIALIZABLE;

  ErrorUtil::checkError(_hdbc, SQLSetConnectAttr(_hdbc, SQL_ATTR_TXN_ISOLATION,
                                                 (SQLPOINTER)isolation, 0));
}

Boolean ODBC::hasTransactionIsolation(Int level) {
  // if (isTransaction()) throw InvalidAccessException();

  Boolean retval = true;
  Int old = getTransactionIsolation();
  try {
    setTransactionIsolation(level);
  } catch (Exception&) {
    retval = false;
  }
  setTransactionIsolation(old);
  return retval;
}

Int ODBC::maxStatementLength() {
  SQLUINTEGER info;
  SQLRETURN rc = 0;
  THROW_IF(ErrorUtil::isError(SQLGetInfo(_hdbc, SQL_MAXIMUM_STATEMENT_LENGTH,
                                         (SQLPOINTER)&info, 0, 0)),
           ConnectionException, "SQLGetInfo(SQL_MAXIMUM_STATEMENT_LENGTH)");
  return info;
}

String ODBC::connectionString() const { return ""; }

Int ODBC::transactionIsolation(SQLULEN isolation) {
  THROW_IF(0 == isolation, ArgumentException,
           "transactionIsolation(SQLUINTEGER)");

  Int ret = 0;
  if (isolation & SQL_TXN_READ_UNCOMMITTED) ret |= TRANSACTION_READ_UNCOMMITTED;

  if (isolation & SQL_TXN_READ_COMMITTED) ret |= TRANSACTION_READ_COMMITTED;

  if (isolation & SQL_TXN_REPEATABLE_READ) ret |= TRANSACTION_REPEATABLE_READ;

  if (isolation & SQL_TXN_SERIALIZABLE) ret |= TRANSACTION_SERIALIZABLE;

  THROW_IF(0 == ret, ArgumentException, "transactionIsolation(SQLUINTEGER)");
  return ret;
}

Boolean ODBC::isString(SQLPOINTER pValue, SQLINTEGER length) {
  return (SQL_NTS == length || length > 0) && pValue;
}

SQLINTEGER ODBC::stringLength(SQLPOINTER pValue, SQLINTEGER length) {
  if (SQL_NTS != length) return length;

  return (SQLINTEGER)std::strlen((const char*)pValue);
}

Boolean ODBC::SQLGetConnectAttrImpl(SQLINTEGER fAttribute, SQLPOINTER rgbValue,
                                    SQLINTEGER cbValueMax,
                                    SQLINTEGER* pcbValue) {
  return !ErrorUtil::isError(
      SQLGetConnectAttr(_hdbc, fAttribute, rgbValue, cbValueMax, pcbValue));
}

Boolean ODBC::SQLGetInfoImpl(SQLUSMALLINT fInfoType, SQLPOINTER rgbInfoValue,
                             SQLSMALLINT cbInfoValueMax,
                             SQLSMALLINT* pcbInfoValue) {
  return !ErrorUtil::isError(
      SQLGetInfo(_hdbc, fInfoType, rgbInfoValue, cbInfoValueMax, pcbInfoValue));
}

}  // namespace sql
}  // namespace gemini