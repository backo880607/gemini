#ifndef GEMINI_SQL_ODBC_INCLUDE
#define GEMINI_SQL_ODBC_INCLUDE
#include "../ConnectionImpl.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#include <Windows.h>
#endif
#include <sqltypes.h>
#include <mutex>

namespace gemini {
namespace sql {

class StatementImpl;
class ODBC : public ConnectionImpl {
  enum TransactionCapability {
    ODBC_TXN_CAPABILITY_UNKNOWN = -1,
    ODBC_TXN_CAPABILITY_FALSE = 0,
    ODBC_TXN_CAPABILITY_TRUE = 1
  };

 public:
  ODBC();
  ~ODBC();

  virtual Boolean open() override;
  virtual void close() override;

  virtual Boolean isConnected() override;

  virtual std::shared_ptr<StatementImpl> createStatement() override;

  virtual Boolean getAutoCommit() override;
  virtual void setAutoCommit(Boolean autoCommit) override;
  virtual void begin() override;
  virtual void commit() override;
  virtual void rollback() override;

  virtual Boolean canTransact() override;
  virtual Boolean isTransaction() override;
  virtual Int getTransactionIsolation() override;
  virtual void setTransactionIsolation(Int level) override;
  virtual Boolean hasTransactionIsolation(Int level) override;

  virtual Int maxStatementLength() override;

 protected:
  virtual String connectionString() const override;
  Int transactionIsolation(SQLULEN isolation);

  Boolean isString(SQLPOINTER pValue, SQLINTEGER length);
  SQLINTEGER stringLength(SQLPOINTER pValue, SQLINTEGER length);
  Boolean SQLGetConnectAttrImpl(SQLINTEGER fAttribute, SQLPOINTER rgbValue,
                                SQLINTEGER cbValueMax, SQLINTEGER* pcbValue);

  Boolean SQLGetInfoImpl(SQLUSMALLINT fInfoType, SQLPOINTER rgbInfoValue,
                         SQLSMALLINT cbInfoValueMax, SQLSMALLINT* pcbInfoValue);

 private:
  friend class ODBCStatement;
  Char _canTransact;
  SQLHENV _henv;  ///< 环境句柄
  SQLHDBC _hdbc;	///< 数据源句柄
  std::mutex _mutex;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_ODBC_INCLUDE