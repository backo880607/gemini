#ifndef GEMINI_SQL_Oracle_INCLUDE
#define GEMINI_SQL_Oracle_INCLUDE
#include "../ado/AdoOracle.h"

namespace gemini {
namespace sql {

class Oracle : public AdoOracle {
 public:
  Oracle();
  ~Oracle();

  virtual std::shared_ptr<StatementImpl> createStatement() override;
  virtual String systemDatabase() const override;
  virtual String databaseExisted(const String &databaseName) const override;
  virtual String createDatabase(const String &databaseName) const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_Oracle_INCLUDE