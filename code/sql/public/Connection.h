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

  Boolean open();
  Boolean open(SQL_TYPE type, const SQLConfig &config);

  void close();

  Boolean isConnected();

  Boolean getAutoCommit();
  void setAutoCommit(Boolean autoCommit);
  void begin();
  void commit();
  void rollback();

  Boolean canTransact();
  Boolean isTransaction();
  Int getTransactionIsolation();
  void setTransactionIsolation(Int level);
  Boolean hasTransactionIsolation(Int level);
  Boolean isTransactionIsolation(Int level);

  Int maxStatementLength();

 private:
  friend class Statement;
  impl_type _impl;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_Connection_INCLUDE