#ifndef GEMINI_SQL_Ado_INCLUDE
#define GEMINI_SQL_Ado_INCLUDE
#include "../ConnectionImpl.h"
#include "AdoCommon.h"

namespace gemini {
namespace sql {

class Ado : public ConnectionImpl {
 public:
  Ado();
  ~Ado();

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
  virtual String connectionString() const = 0;

 private:
  friend class AdoStatement;
  ADODB::_ConnectionPtr _conn;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_Ado_INCLUDE