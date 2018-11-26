#ifndef GEMINI_SQL_Connection_INCLUDE
#define GEMINI_SQL_Connection_INCLUDE
#include "SQLConfig.h"

namespace gemini {
namespace sql {

class ConnectionImpl;
class GEMINI_SQL_API Connection final {
  typedef std::shared_ptr<ConnectionImpl> impl_type;

 public:
  Connection();
  ~Connection();

  Boolean valid() const { return _impl != nullptr; }

  const SQLConfig& getConfig() const;

  Driver* getDriver();
  void setDriver(Driver* driver);

  void open();
  void open(SQL_TYPE type, const SQLConfig& config);

  void close();

  Boolean isConnected();

  Boolean getAutoCommit();
  void setAutoCommit(Boolean autoCommit);
  void begin();
  void commit();
  void rollback();

  Int getTransactionIsolation();
  void setTransactionIsolation(Int level);
  Boolean hasTransactionIsolation(Int level);
  Boolean isTransactionIsolation(Int level);

 private:
  friend class Statement;
  friend class Driver;
  impl_type _impl;
};

class GEMINI_SQL_API CheckDatabase {
 public:
  CheckDatabase();
  ~CheckDatabase();

  void execute(SQL_TYPE type, const SQLConfig& config);
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Connection_INCLUDE