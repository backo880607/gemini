#ifndef GEMINI_SQL_AdoStatement_INCLUDE
#define GEMINI_SQL_AdoStatement_INCLUDE
#include "../StatementImpl.h"
#include "AdoCommon.h"

#include <sstream>

namespace gemini {
namespace sql {

class Ado;
class AdoStatement : public StatementImpl {
 protected:
  AdoStatement(Ado &conn);

 public:
  ~AdoStatement();

  virtual void reset() override;

  virtual StatementImpl &operator<<(const Char *value) override {
    _ostr << value;
    return *this;
  }
  virtual String toString() const override { return _ostr.str(); }

  virtual std::shared_ptr<ResultSetImpl> execute(Long &affectRows) override;

 protected:
  virtual Binder *createBinder() override;

 private:
  std::ostringstream _ostr;
  ADODB::_CommandPtr _stmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_AdoStatement_INCLUDE