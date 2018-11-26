#ifndef GEMINI_SQL_MySQL_INCLUDE
#define GEMINI_SQL_MySQL_INCLUDE
//#include "../poco/PocoMySQL.h"
#include "../ado/AdoMySQL.h"

namespace gemini {
namespace sql {

class MySQL : public AdoMySQL {
 public:
  MySQL();
  ~MySQL();

  virtual std::shared_ptr<StatementImpl> createStatement() override;
  virtual String systemDatabase() const override;
  virtual String databaseExisted(const String &databaseName) const override;
  virtual String createDatabase(const String &databaseName) const override;
};

}  // namespace sql
}  // namespace gemini
#endif  // !GEMINI_SQL_MySQL_INCLUDE