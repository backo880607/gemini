#ifndef GEMINI_SQL_SQLite_INCLUDE
#define GEMINI_SQL_SQLite_INCLUDE
#include "../ConnectionImpl.h"

#include <mutex>

extern "C" {
typedef struct sqlite3 sqlite3;
};

namespace gemini {
namespace sql {

class StatementImpl;
class SQLite : public ConnectionImpl {
 public:
  SQLite();
  ~SQLite();

  virtual void open() override;

  virtual Boolean isConnected() override { return _pDB != nullptr; }

  virtual Boolean getAutoCommit() override;
  virtual void setAutoCommit(Boolean autoCommit) override;
  virtual void begin() override;
  virtual void commit() override;
  virtual void rollback() override;

  virtual Int getTransactionIsolation() override {
    return TRANSACTION_READ_COMMITTED;
  }
  virtual void setTransactionIsolation(Int level) override;
  virtual Boolean hasTransactionIsolation(Int level) override {
    return level == TRANSACTION_READ_COMMITTED;
  }
  virtual Boolean isTransactionIsolation(Int level) override {
    return level == TRANSACTION_READ_COMMITTED;
  }

  virtual std::shared_ptr<StatementImpl> createStatement() override;

  virtual String systemDatabase() const override;
  virtual String databaseExisted(const String &databaseName) const override;
  virtual String createDatabase(const String &databaseName) const override;

 protected:
  virtual void onClose() override;
  //virtual String connectionString() const override { return getConfig().ip; }

 private:
  sqlite3 *_pDB;
  std::mutex _mutex;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_SQLite_INCLUDE