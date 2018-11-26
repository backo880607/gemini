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
  ConnectionImpl();

 public:
  virtual ~ConnectionImpl();

  Driver *getDriver() { return _driver; }
  void setDriver(Driver *driver) { _driver = driver; }

  const SQLConfig &getConfig() const { return _config; }

  virtual void open() = 0;
  void open(const SQLConfig &config);
  void close();

  virtual Boolean isConnected() = 0;

  virtual Boolean getAutoCommit() = 0;
  virtual void setAutoCommit(Boolean autoCommit) = 0;
  virtual void begin() = 0;
  virtual void commit() = 0;
  virtual void rollback() = 0;

  virtual Int getTransactionIsolation() = 0;
  virtual void setTransactionIsolation(Int level) = 0;
  virtual Boolean hasTransactionIsolation(Int level) = 0;
  virtual Boolean isTransactionIsolation(Int level) = 0;

  virtual std::shared_ptr<StatementImpl> createStatement() = 0;

  virtual String systemDatabase() const = 0;
  virtual String databaseExisted(const String &databaseName) const = 0;
  virtual String createDatabase(const String &databaseName) const = 0;

 protected:
  virtual void onClose() = 0;

 protected:
  friend class StatementImpl;

 private:
  Driver *_driver;
  SQLConfig _config;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_ConnectionImpl_INCLUDE