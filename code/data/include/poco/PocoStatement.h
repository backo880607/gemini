#ifndef GEMINI_SQL_PocoStatement_INCLUDE
#define GEMINI_SQL_PocoStatement_INCLUDE
#include "../StatementImpl.h"

namespace Poco {
namespace Data {
class Statement;
}
}  // namespace Poco

namespace gemini {
namespace sql {

class PocoConnection;
class PocoStatement : public StatementImpl {
 protected:
  PocoStatement(PocoConnection &conn);

 public:
  virtual ~PocoStatement();

  virtual void reset() override;

  virtual StatementImpl &operator<<(const Char *value) override;
  virtual String toString() const override;

  virtual std::shared_ptr<ResultSetImpl> execute(Long &affectRows) override;

 protected:
  virtual Binder *createBinder() override;

 private:
  Poco::Data::Statement *_stmt;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_PocoStatement_INCLUDE