#ifndef GEMINI_SQL_PocoConnection_INCLUDE
#define GEMINI_SQL_PocoConnection_INCLUDE
#include "../ConnectionImpl.h"

namespace Poco {
namespace Data {
class Session;
}
}  // namespace Poco

namespace gemini {
namespace sql {

class PocoConnection : public ConnectionImpl {
 public:
  virtual void open() override;

  virtual Boolean isConnected() override;

  virtual Boolean getAutoCommit() override;
  virtual void setAutoCommit(Boolean autoCommit) override;
  virtual void begin() override;
  virtual void commit() override;
  virtual void rollback() override;

  virtual Int getTransactionIsolation() override;
  virtual void setTransactionIsolation(Int level) override;
  virtual Boolean hasTransactionIsolation(Int level) override;
  virtual Boolean isTransactionIsolation(Int level) override;

 protected:
  virtual void onClose() override;
  virtual String connector() const = 0;
  virtual String connectionString() const = 0;

 protected:
  friend class PocoStatement;
  Poco::Data::Session* _session;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_PocoConnection_INCLUDE