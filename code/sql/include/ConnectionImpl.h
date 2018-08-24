#ifndef GEMINI_SQL_ConnectionImpl_INCLUDE
#define GEMINI_SQL_ConnectionImpl_INCLUDE
#include "../public/SQLConfig.h"

namespace gemini {
namespace sql {

class StatementImpl;
class ConnectionImpl {
  ConnectionImpl(const ConnectionImpl &) = delete;
  ConnectionImpl &operator=(const ConnectionImpl &) = delete;

 protected:
  ConnectionImpl() {}

 public:
  virtual ~ConnectionImpl() { close(); }

  const SQLConfig &getConfig() const { return _config; }

  virtual Boolean open() = 0;
  virtual Boolean open(const SQLConfig &config);
  virtual void close(){};

  virtual Boolean isConnected() = 0;

  virtual std::shared_ptr<StatementImpl> createStatement() = 0;

  virtual Boolean getAutoCommit() = 0;
  virtual void setAutoCommit(Boolean autoCommit) = 0;
  virtual void begin() = 0;
  virtual void commit() = 0;
  virtual void rollback() = 0;

  virtual Boolean canTransact() = 0;
  virtual Boolean isTransaction() = 0;
  virtual Int getTransactionIsolation() = 0;
  virtual void setTransactionIsolation(Int level) = 0;
  virtual Boolean hasTransactionIsolation(Int level) = 0;
  virtual Boolean isTransactionIsolation(Int level);

  virtual Int maxStatementLength() = 0;

 protected:
  virtual String connectionString() const = 0;

 protected:
  Boolean _inTransaction;

 private:
  SQLConfig _config;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_ConnectionImpl_INCLUDE