#ifndef GEMINI_SQL_SQLServer_INCLUDE
#define GEMINI_SQL_SQLServer_INCLUDE
//#include "../ado/AdoSQLServer.h"
#include "../poco/PocoSQLServer.h"

namespace gemini {
namespace sql {

class SQLServer : public PocoSQLServer {
 public:
  SQLServer();
  ~SQLServer();

  virtual std::shared_ptr<StatementImpl> createStatement() override;
  virtual String systemDatabase() const override;
  virtual String databaseExisted(const String &databaseName) const override;
  virtual String createDatabase(const String &databaseName) const override;
};

class Access : public SQLServer {
 public:
  Access();
  ~Access();
};

class SQLExcel : public SQLServer {
 public:
  SQLExcel();
  ~SQLExcel();
};

}  // namespace sql
}  // namespace gemini
#endif  // GEMINI_SQL_SQLServer_INCLUDE